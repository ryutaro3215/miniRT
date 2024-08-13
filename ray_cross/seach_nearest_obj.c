/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seach_nearest_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:08:42 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/08/13 11:18:41 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static double calc_distance(t_object *obj, double x, double y)
{
    if(obj->type == SPHERE)
        return (calc_sp_distance(obj, x, y));
    else if(obj->type == PLANE)
        return(calc_pl_distance(obj, x, y));
    else if(obj->type == CYLINDER)
        return(calc_cy_distance(obj, x, y));
}

t_object seach_nearest_obj(t_rt *rt, double x, double y)
{
    t_object    *nearest_obj;
    t_object    *obj;
    t_object    *tmp;
    double      distance;
    double      min_distance;
    
    // TODO defineで定義するようにする
    min_distance = 1000000000;

    nearest_obj = NULL;
    obj = rt->scene->object;
    while(obj)
    {
        distance = 0;
        distance = calc_distance(obj, x, y);
        if(distance < min_distance)
        {
            min_distance = distance;
            nearest_obj = obj;
        }
        obj = obj->next;
    }
}