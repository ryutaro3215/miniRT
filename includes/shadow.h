/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:42:17 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/10/09 13:08:05 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADOW_H
# define SHADOW_H

#include "minirt.h"

bool  is_shadow(t_scene *scene ,t_object *nearest_obj, t_vec3 dir_vec);
int phong_calc(t_rt *rt, t_vec3 dir_vec,t_object *nearest_obj);
t_rgb   color_init2(double r, double g, double b);
t_rgb color_mul(t_rgb a, t_rgb b);
t_rgb color_mul_scalar(t_rgb a, double b);
t_rgb color_add(t_rgb a, t_rgb b);
uint32_t color_ans(int r,int g , int b);
t_rgb check_color_is_valid(t_rgb a);
t_rgb nearest_objs_color(t_object *nearest_obj);
t_rgb get_light_color(t_rt *rt);
t_rgb get_ambi_light_color(t_rt *rt);
#endif
