//
//  shaders.h
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

#ifndef SRT_SHADERS_H
#define SRT_SHADERS_H

#include "raymath.h"

void trace( scene_t* scene, Vec3 out_color, ray_t* ray, int recursion_depth );


void constant_shader( Vec3 out_color,
                     scene_t* scene,
                     sphere_t* sphere,
                     ray_t* original_ray,
                     double hit_on_ray,
                     int recursion_depth );

void lambertian_shader( Vec3 out_color,
                       scene_t* scene,
                       sphere_t* sphere,
                       ray_t* original_ray,
                       double hit_on_ray,
                       int recursion_depth );

void phong_shader( Vec3 out_color,
                   scene_t* scene,
                   sphere_t* sphere,
                   ray_t* original_ray,
                   double hit_on_ray,
                   int recursion_depth );

void mirror_shader( Vec3 out_color,
                    scene_t* scene,
                    sphere_t* sphere,
                    ray_t* original_ray,
                    double hit_on_ray,
                    int recursion_depth );


#endif
