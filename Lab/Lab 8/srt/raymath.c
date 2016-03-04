//
//  math.c
//  srt
//
//  Created by vector on 11/2/10.
//  Copyright (c) 2010 Brian F. Allen.

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

#include "raymath.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

const long double PI = 3.1415926535897932384626433832795028841968;
const double dEpsilon = 1e-12;     /* for ray-intersect test */
const double dInfinity = 1.0/0.0;


#define VEC( OP, out, a, b ) \
  for( int i=0; i<3; ++i ) (out)[i] = (a)[i] OP (b)[i]

void zero( Vec3 out )
{
    memset( out, 0, sizeof (Vec3) );
}

void set( Vec3 out, double x, double y, double z )
{
    out[0] = x; out[1] = y; out[2] = z;
}

void copy( Vec3 to, Vec3 from )
{
    memcpy( to, from, sizeof (Vec3) );
}

void add( Vec3 out, Vec3 a, Vec3 b )
{
	VEC( +, out, a, b );
}
void sub( Vec3 out, Vec3 a, Vec3 b )
{
	VEC( -, out, a, b );
}
void mul( Vec3 out, Vec3 a, double s )
{
	for( int i=0; i<3; ++i )
	{
		out[i] = a[i] * s;
	}
}
double dot( Vec3 a, Vec3 b )
{
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}
double len( Vec3 a )
{
    return sqrt( dot( a,a ) );
}

void cross( Vec3 out, Vec3 a, Vec3 b )
{
	out[0] = a[1]*b[2] - a[2]*b[1];
	out[1] = a[2]*b[0] - a[0]*b[2];
	out[2] = a[0]*b[1] - a[1]*b[0];
}
void norm( Vec3 out, Vec3 a )
{
	double recipLen = 1.0/sqrt( dot(a,a) );
	for( int i=0;i<3;++i )
	{
		out[i] = a[i] * recipLen;
	}
}

void reflect( Vec3 out, Vec3 incoming, Vec3 surf_norm )
{
    Vec3 n;
    norm( n, surf_norm );
    Vec3 v;
    norm( v, incoming );
    Vec3 norm_comp;
    mul( norm_comp, n, -2.0 * dot( v, n ) );
    add( out, v, norm_comp );
    norm( out, out );
}

/*
 * Sphere
 */
void sphere_normal( Vec3 out, sphere_t* s, Vec3 dir )
{
	sub( out, dir, s->org );
	mul( out, out, 1.0/(s->rad) );
}

double sphere_intersect( sphere_t* sphere, ray_t* ray )
{
	Vec3 v;
	sub( v, sphere->org, ray->org );
	double b = dot( ray->dir, v );
	double disc = b*b - dot(v,v) + sphere->rad*sphere->rad;
	if( disc < 0.0 )
	{
		return dInfinity;
	}
	double d = sqrt( disc );
	double t1 = b-d;
	double t2 = b+d;
	if( t2 < 0.0 )
	{
		return dInfinity;
	}
	else
	{
		return( t1 > 0.0 ? t1 : t2 );
	}
}

void sphere_copy( sphere_t* to, sphere_t* from )
{
	copy ( to->org, from->org );
	to->rad = from->rad;
}


void init_scene( scene_t* scene )
{
    scene->sphere_count = 0;
    scene->spheres = NULL;
    scene->light_count = 0;
    scene->lights = NULL;
}

sphere_t* add_sphere( scene_t* scene,
                      double x, double y, double z,
                      double radius,
                      double r, double g, double b )
{
    (scene->sphere_count)++;
    scene->spheres = realloc( scene->spheres,
                              sizeof(sphere_t)*scene->sphere_count );
    sphere_t* sphere = &(scene->spheres[(scene->sphere_count) - 1]);
    set( sphere->org, x, y, z );
    sphere->rad = radius;
    set( sphere->color, r, g, b );
    sphere->shader = NULL;
    return sphere;
}

light_t* add_light( scene_t* scene, double x, double y, double z,
                    double r, double g, double b )
{
    (scene->light_count)++;
    scene->lights = realloc( scene->lights,
                             sizeof(light_t)*scene->light_count );
    light_t* light = &(scene->lights[ scene->light_count - 1 ]);
    set( light->pos, x, y, z );
    set( light->color, r, g, b );
    return light;
}

double gamma( double raw )
{
    /* encode with a gamma of 0.45 (according to wikipedia */
    /* TODO */
    return raw;
}

/*
 * Test functions
 */
int is_close( double a, double b )
{
    return fabs( a - b ) < 1e-5;
}
