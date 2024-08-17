/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cross.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:24:39 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/08/18 00:35:29 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CROSS_H
# define RAY_CROSS_H

# include "minirt.h"
#include "shadow.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>

#define DISTANCE_MAX 1000000
void	draw_sphere(t_rt *rt,double x, double y, t_object *nearest_obj);
double	discriminant(t_rt *rt, t_vec3 screen_vec, t_object *object);
void	draw_plane(t_rt *rt, double x, double y, t_object *nearest_obj);
void   draw_object(t_rt *rt);
double	cross_ray_plane(t_object *object, t_vec3 screen_vec, t_camera *camera);
t_vec3	*get_intersections(t_rt *rt, t_vec3 dir, t_vec3 cam2cyl);
bool	is_height_range(t_rt *rt, t_vec3 *intersections);
bool	discriminant_cylinder(t_rt *rt, t_vec3 screen_vec);
void	draw_cylinder(t_rt *rt, double x, double y, t_object *nearest_obj);
t_object *seach_nearest_obj(t_rt *rt, double x, double y);
double calc_distance(t_object *obj, t_vec3 screen_vec, t_vec3 *source_point);

#endif
