//
//  shaders.c
//  srt
//
//  Created by vector on 11/2/10.
//  Copyright (c) 2010 Brian F. Allen. All rights reserved.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "shaders.h"
#include <assert.h>
#include <math.h>


/*
 * trace ray into the scene.  if it hits an object,
 * run the object's shader to figure out the out_color
 * can be recursive, so may want to stop at a given recursion_depth
 */
void trace( scene_t* scene, Vec3 out_color, ray_t* ray, int recursion_depth )
{
    double closest_depth = dInfinity;
    int closest_index = -1;
    for( int i=0; i<scene->sphere_count; ++i )
    {
        double depth = sphere_intersect( &(scene->spheres[i]), ray );
        if( depth < closest_depth )
        {
            closest_depth = depth;
            closest_index = i;
        }
    }
    if( closest_index != -1 && scene->spheres[closest_index].shader )
    {
        /* hitting sphere[closest_index] */
        /* call the sphere's shading function */
        (*(scene->spheres[closest_index].shader))( out_color,
                scene, &(scene->spheres[closest_index]),
                ray, closest_depth, recursion_depth + 1 );
    }
}

/*
 ****************************************************
 * Helper functions for shaders
 ****************************************************
 */

/* does ray hit some other scene object between the surf and light?
 */
static int
is_segment_blocked( scene_t* scene, sphere_t* curr_sphere,
		    ray_t* ray, double depth_to_light )
{
    for( int i=0; i<scene->sphere_count; ++i )
    {
        if( &(scene->spheres[i]) == curr_sphere )
        {
            continue; /* ignore self-shadowing (these are convex objects) */
        }
        double depth_to_sphere = sphere_intersect( &(scene->spheres[i]), ray );
        if( depth_to_light > depth_to_sphere )
        {
            return 1; /* blocked */
        }
    }
    return 0;
}

static void
surf_pos_and_normal( Vec3 out_surf_pos,
		     Vec3 out_surf_norm,
		     sphere_t* sphere,
		     ray_t* original_ray,
		     double hit_on_ray )
{
    mul( out_surf_pos, original_ray->dir, hit_on_ray );
    add( out_surf_pos, original_ray->org, out_surf_pos );
    sub( out_surf_norm, out_surf_pos, sphere->org );
    norm( out_surf_norm, out_surf_norm );
}



/*
 ****************************************************
 * Shaders
 ****************************************************
 */


/* every point on the sphere is of a single color, no matter
 * what lighting or where the viewer is
 */
void constant_shader( Vec3 out_color,
                     scene_t* scene,
                     sphere_t* sphere,
                     ray_t* original_ray,
                     double hit_on_ray,
                     int recursion_depth )
{
    copy( out_color, sphere->color );
}



/* "diffuse" shader where the color
 * of the ray depends only on the hit sphere
 * and the light.
 * The surface is brighter the closer
 * the surface normal is to the direction of the light.
 * The color of the surface doesn't depend at all on the
 * direction of the incoming ray.
 */
void lambertian_shader( Vec3 out_color,
                       scene_t* scene,
                       sphere_t* sphere,
                       ray_t* original_ray,
                       double hit_on_ray,
                       int recursion_depth )
{
    /* ensure the ray has a normalized dir */
    assert( is_close( 1, dot( original_ray->dir, original_ray->dir ) ) );
    assert( hit_on_ray >= 0 );
    set( out_color, 0,0,0 );

    Vec3 surf_pos;
    Vec3 surf_norm;
    surf_pos_and_normal( surf_pos, surf_norm, sphere, original_ray, hit_on_ray );

    /* for each light, intensity = surface normal dot light direction.
     */
    for( int i=0; i<scene->light_count; ++i )
    {
        /* compute direction and distance from surface to light */
        light_t* light = &(scene->lights[i]);
        ray_t surf_to_light;
        copy( surf_to_light.org, surf_pos );
        sub( surf_to_light.dir, light->pos, surf_pos );
        double depth_to_light = len( surf_to_light.dir );
        norm( surf_to_light.dir, surf_to_light.dir );
        if( is_segment_blocked( scene, sphere, &surf_to_light, depth_to_light ) )
        {
            continue; /* there's something inbetween our surface point
                       * and this light, so we're effectively in shadow.
                       * Skip this light entirely.  If transparency or
                       * transluncy is implemented, this would change. */
        }
        /* add illuminatation from light */
        for( int c=0; c<3; c++ )
        {
            /* note max is used so that lights cannot reduce illumination,
             * even when illuminating the underside of a surface
             */
            out_color[c] +=   light->color[c] * sphere->color[c]
            * fmax( 0.0, dot( surf_to_light.dir, surf_norm ) );
        }

    }
}


/* Simple shader with a specular component.
 * Looks like shiny plastic.
 */
void phong_shader( Vec3 out_color,
                   scene_t* scene,
                   sphere_t* sphere,
                   ray_t* original_ray,
                   double hit_on_ray,
                   int recursion_depth )
{
    /* scale factors for how much each kind of lighting affects the color */
    const double specular = 0.2;
    const double diffuse = 0.3;
    const double ambient = 0.5;

    /* specularity, how shiny the surface is */
    const double shininess = 3.3;

    set( out_color, 0,0,0 );
    Vec3 surf_pos;
    Vec3 surf_norm;
    surf_pos_and_normal( surf_pos, surf_norm, sphere, original_ray, hit_on_ray );

    /* ambient componnet is independent of lights */
    mul( out_color, sphere->color, ambient );

    /* for each light, intensity = surface normal dot light direction.
     */
    for( int i=0; i<scene->light_count; ++i )
    {
        /* compute direction and distance from surface to light */
        light_t* light = &(scene->lights[i]);
        ray_t surf_to_light;
        copy( surf_to_light.org, surf_pos );
        sub( surf_to_light.dir, light->pos, surf_pos );
        double depth_to_light = len( surf_to_light.dir );
        norm( surf_to_light.dir, surf_to_light.dir );
        if( is_segment_blocked( scene, sphere, &surf_to_light, depth_to_light ) )
        {
            continue; /* there's something inbetween our surface point
                       * and this light, so we're effectively in shadow.
                       * Skip this light entirely.  If transparency or
                       * transluncy is implemented, this would change. */
        }
        /* add illuminatation from light */
        for( int c=0; c<3; c++ )
        {
            assert( is_close( dot( surf_norm, surf_norm ), 1.0 ) );

            /* diffuse component */
            out_color[c] += diffuse * light->color[c] * sphere->color[c]
            * fmax( 0.0, dot( surf_to_light.dir, surf_norm ) );

            /* specular component */
            Vec3 view_dir; /* backwards of direction of original ray */
            mul( view_dir, original_ray->dir, -1. );
            norm( view_dir, view_dir );

            Vec3 light_reflect_dir; /* direction that light is bouncing off surface */
            reflect( light_reflect_dir, surf_to_light.dir, surf_norm );

            /* v - (2 dot(v,n)n ) */


            assert( is_close( dot( original_ray->dir, original_ray->dir), 1.0 ) );
            assert( is_close( dot( light_reflect_dir, light_reflect_dir ), 1.0 ) );

            double spec = fmax( dot( light_reflect_dir, original_ray->dir ), 0. );
            if( spec > 0 )
            {
                out_color[c] += specular * pow( spec, shininess );
            }
        }
    }
}


void mirror_shader( Vec3 out_color,
                   scene_t* scene,
                   sphere_t* sphere,
                   ray_t* original_ray,
                   double hit_on_ray,
                   int recursion_depth )
{
    double reflectivity = 0.35;
    Vec3 surf_pos;
    Vec3 surf_norm;
    surf_pos_and_normal( surf_pos, surf_norm, sphere, original_ray, hit_on_ray );

    ray_t outbound;
    copy( outbound.org, surf_pos );
    reflect( outbound.dir, original_ray->dir, surf_norm );

    /* need to offset slightly off the surface, else ray hits this sphere again */
    Vec3 offset;
    mul( offset, outbound.dir, 1e-6 );
    add( outbound.org, outbound.org, offset );

    Vec3 reflected_color;
    set( reflected_color, 0,0,0 );
    if( recursion_depth < 5 )
    {
        trace( scene, reflected_color, &outbound, recursion_depth + 1 );
        mul( reflected_color, reflected_color, reflectivity );
    }
    else
    {
        reflectivity = 0;
    }
    Vec3 base_color;
    set( base_color, 0, 0, 0 );
    lambertian_shader( base_color,
                       scene,
                       sphere,
                       original_ray,
                       hit_on_ray,
                       recursion_depth + 1 );
    //mul( base_color, base_color, (1.0 - reflectivity) );
    add( out_color, base_color, reflected_color );
}
