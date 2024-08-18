/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:42:17 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/08/18 00:46:03 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADOW_H
# define SHADOW_H

#include "minirt.h"
#include "ray_cross.h"

bool  is_shadow(t_scene *scene ,double t, t_vec3 dir_vec);
int phong_calc(t_scene *scene, t_vec3 dir_vec,t_object *nearest_obj);
#endif