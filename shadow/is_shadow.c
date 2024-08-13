/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:36:45 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/08/13 20:01:17 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// TODO なぜか関数が消えていたので再度実装する必要あり
bool is_shadow(t_scene *scene ,double t, t_vec3 dir_vec)
{
    t_vec3 p = vec3_add(*scene->camera->view_point, vec3_mul(dir_vec, t));
    t_vec3 intersec2light = vec3_sub(*scene->light->light_point, p);
    t_vec3 l = vec3_norm(intersec2light);
    t_vec3 start = vec3_add(p, vec3_mul(l, 0.0001));
}