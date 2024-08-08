/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cross.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:24:39 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/08/08 20:34:53 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CROSS_H
# define RAY_CROSS_H

# include "minirt.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>

void	draw_sphere(t_rt *rt,double x, double y);
double	discriminant(t_rt *rt, t_vec3 screen_vec);
void	draw_plane(t_rt *rt, double x, double y);
void   draw_object(t_rt *rt);
double	cross_ray_plane(t_rt *rt, t_vec3 screen_vec);
t_vec3	*get_intersections(t_rt *rt, t_vec3 dir, t_vec3 cam2cyl);
bool	is_height_range(t_rt *rt, t_vec3 *intersections);
bool	discriminant_cylinder(t_rt *rt, t_vec3 screen_vec);
void	draw_cylinder(t_rt *rt);

#endif
