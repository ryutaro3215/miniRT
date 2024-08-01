/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cross.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:24:39 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/08/01 22:30:37 by rmatsuba         ###   ########.fr       */
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

void	draw_sphere(t_rt *rt);
double	discriminant(t_rt *rt, t_vec3 screen_vec);
void	draw_plane(t_rt *rt);
double	cross_ray_plane(t_rt *rt, t_vec3 screen_vec);

#endif
