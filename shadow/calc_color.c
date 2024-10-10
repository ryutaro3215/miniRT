/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshida <kyoshida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:07:11 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/10/10 19:39:53 by kyoshida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shadow.h"
#include "../includes/ray_cross.h"

t_rgb nearest_objs_color(t_object *nearest_obj)
{
    t_rgb   color;
    double red = nearest_obj->rgb->r;
    double green = nearest_obj->rgb->g;
    double blue = nearest_obj->rgb->b;

    color = check_color_is_valid(color_init2(red,green,blue));

    return color;
}
t_rgb get_light_color(t_rt *rt)
{
    t_rgb color;

    double red = rt->scene->light->rgb->r;
    double green = rt->scene->light->rgb->g;
    double blue = rt->scene->light->rgb->b;
    color = check_color_is_valid(color_init2(red,green,blue));
    return color;
}
t_rgb get_ambi_light_color(t_rt *rt)
{
    t_rgb color;

    double red = rt->scene->ambi_light->rgb->r;
    double green = rt->scene->ambi_light->rgb->g;
    double blue = rt->scene->ambi_light->rgb->b;
    color = check_color_is_valid(color_init2(red,green,blue));
    return color;
}