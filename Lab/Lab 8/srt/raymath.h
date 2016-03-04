#ifndef SRT_RAYMATH_H
#define SRT_RAYMATH_H
//
//  math.h
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

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

extern const long double PI;

extern const double dEpsilon;     /* for ray-intersect test */
extern const double dInfinity;

typedef double Vec3[3];


typedef struct sphere_struct sphere_t;


typedef struct
{
	Vec3 org;    /* origin */
	Vec3 dir;    /* direction */
} ray_t;


typedef struct
{
    Vec3 pos;
    Vec3 color;
} light_t;

typedef struct
{
    light_t* lights;
    int light_count;
    sphere_t* spheres;
    int sphere_count;
} scene_t;

void init_scene( scene_t* scene );

sphere_t* add_sphere( scene_t* scene,
                      double x, double y, double z,
                      double radius,
                      double r, double g, double b );

light_t* add_light( scene_t* scene,
                    double x, double y, double z,
                    double r, double g, double b );



typedef void (*shader_func_t)( Vec3 out_color,
                               scene_t* scene,
                               sphere_t* sphere,
                               ray_t* original_ray,
                               double hit_on_ray,
                               int recursion_depth );

struct sphere_struct
{
	Vec3          org;    /* center */
	double        rad;    /* radius */
    Vec3          color;  /* surface color */
    shader_func_t shader; /* surface shader */
};

/* holds the normal and distance away
 * that an intersection was found.
 */
typedef struct
{
    Vec3   n;    /* normal */
	double t;    /* distance */
} hit_t;

void   zero( Vec3 out );
void   set( Vec3 out, double x, double y, double z );
void   copy( Vec3 to, Vec3 from );
void   add( Vec3 out, Vec3 a, Vec3 b );
void   sub( Vec3 out, Vec3 a, Vec3 b );
void   mul( Vec3 out, Vec3 a, double s );
double dot( Vec3 a, Vec3 b );
double len( Vec3 a );
void   cross( Vec3 out, Vec3 a, Vec3 b );
void   norm( Vec3 out, Vec3 a );
void   reflect( Vec3 out, Vec3 incoming, Vec3 surf_norm );
void   sphere_normal( Vec3 out, sphere_t* s, Vec3 dir );

double gamma( double raw );

/* returns the distance along ray of first interestion with sphere
 * post: return is positive (since it's a ray and not a line)
 */
double sphere_intersect( sphere_t* sphere, ray_t* ray );

void   sphere_copy( sphere_t* to, sphere_t* from );


/*
 * Test functions
 */
int is_close( double a, double b );

#endif
