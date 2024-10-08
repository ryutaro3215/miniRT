/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cross.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:24:39 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/09 01:13:39 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CROSS_H
# define RAY_CROSS_H

# include "minirt.h"
# include "shadow.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# define DISTANCE_MAX 1000000

// about object
void			draw_object(t_rt *rt);
t_vec3			get_dir(t_rt *rt, double x, double y, t_vec3 cam_center);
t_object		*search_nearest_obj(t_rt *rt, double x, double y);
t_object		*calc_obj_distance(t_vec3 dir, t_rt *rt);
double			calc_distance(t_object *obj, t_vec3 dir, t_vec3 *source_point);

//about sphere
void			draw_sphere(t_rt *rt, double x,
					double y, t_object *nearest_obj);
double			discriminant(t_rt *rt, t_vec3 dir, t_object *object);
double			calc_sp_distance(t_object *object,
					t_vec3 dir, t_vec3 *source_point);

//about 	plane
void			draw_plane(t_rt *rt, double x, double y, t_object *nearest_obj);
bool			judge_denominator(t_vec3 dir,
					t_camera *camera, t_object *object);
double			cross_ray_plane(t_object *object, t_vec3 dir, t_rt *rt);
double			calc_pl_distance(t_object *object,
					t_vec3 dir, t_vec3 *source_point);
//about 	cylinder
void			draw_cylinder(t_rt *rt, double x,
					double y, t_object *nearest_obj);
bool			discriminate_cylinder(t_rt *rt, t_vec3 dir, t_object *object);
bool			judge_inner_outer(t_object *object,
					t_vec3 *center_set, double *h_set);
t_vec3			*get_inter(t_rt *rt, t_vec3 dir,
					t_vec3 cam2cyl, t_object *object);
double			calc_cy_distance(t_object *object,
					t_vec3 dir, t_vec3 *source_point);
double			calc_cy_d(t_object *obj, t_vec3 dir, t_vec3 *source_point);
double			calc_cy_t(t_object *obj, t_vec3 dir,
					int flag, t_vec3 *source_point);
t_vec3			*calc_cy_intersections(t_object *obj, t_vec3 dir,
					t_vec3 *source_point);

#endif
