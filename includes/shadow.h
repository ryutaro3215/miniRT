/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:42:17 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/08/13 17:05:07 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADOW_H
# define SHADOW_H

#include "minirt.h"
#include "ray_cross.h"

int phong_calc(t_scene *scene, t_vec3 dir_vec,t_object *nearest_obj);

#endif