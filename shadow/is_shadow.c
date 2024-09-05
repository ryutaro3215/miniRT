/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:36:45 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/09/04 21:52:59 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/shadow.h"
#include "../includes/ray_cross.h"
// TODO なぜか関数が消えていたので再度実装する必要あり
bool is_shadow(t_scene *scene ,t_object *nearest_obj, t_vec3 dir_vec)
{
    double t = calc_distance(nearest_obj, dir_vec, scene->camera->view_point);
    t_vec3 p = vec3_add(*scene->camera->view_point, vec3_mul(dir_vec, t));
    t_vec3 intersec2light = vec3_sub(*scene->light->light_point, p);
    t_vec3 l = vec3_norm(intersec2light);
    t_vec3 start = vec3_add(p, vec3_mul(l, 0.0001));
    double light_dist = vec3_mag(intersec2light) - 0.0001;
    t_vec3 dir = vec3_norm(vec3_sub(*scene->light->light_point, start));

    // シャドウベクトルが好転とぶつかり、かつ、それが最も近いオブジェクトにぶつかるかどうか
    t_object *object = scene->object;

    while(object)
    {
        double distance = calc_distance(object, dir, &start);
                // printf("distance:%f\n", distance);

        // printf("distance:%f\n", distance);
        if( distance >= 0 && distance <= light_dist)
        
            return true;
        object = object->next;
    }
    return false;
}
