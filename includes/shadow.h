/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:42:17 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/09/03 00:51:48 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADOW_H
# define SHADOW_H

#include "minirt.h"

bool  is_shadow(t_scene *scene ,t_object *nearest_obj, t_vec3 dir_vec);
int phong_calc(t_rt *rt, t_vec3 dir_vec,t_object *nearest_obj);
#endif
