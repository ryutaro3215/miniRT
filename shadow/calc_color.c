/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:07:11 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/10/09 13:07:40 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shadow.h"
#include "../includes/ray_cross.h"

t_rgb nearest_objs_color(t_object *nearest_obj)
{
    t_rgb color;
    // int colorhex = nearest_obj->rgb->r | nearest_obj->rgb->b | nearest_obj->rgb->b;
    // double red = (double)(colorhex >> 16 & 0xff) / 255;
	// double green = (double)(colorhex >> 8 & 0xff) / 255;
	// double blue = (double)(colorhex & 0xff) / 255;
    // double red = nearest_obj->rgb->r/255.0;
    // double green = nearest_obj->rgb->g/255.0;
    // double blue = nearest_obj->rgb->b/255.0;
    double red = nearest_obj->rgb->r;
    double green = nearest_obj->rgb->g;
    double blue = nearest_obj->rgb->b;
    // color = color_init2(red,green,blue);
    color = check_color_is_valid(color_init2(red,green,blue));

    return color;
}
t_rgb get_light_color(t_rt *rt)
{
    t_rgb color;
    // double red = rt->scene->light->rgb->r/255.0;
    // double green = rt->scene->light->rgb->g/255.0;
    // double blue = rt->scene->light->rgb->b/255.0;
    double red = rt->scene->light->rgb->r;
    double green = rt->scene->light->rgb->g;
    double blue = rt->scene->light->rgb->b;
    // color = color_init2(red,green,blue);
    color = check_color_is_valid(color_init2(red,green,blue));
    return color;
}
t_rgb get_ambi_light_color(t_rt *rt)
{
    t_rgb color;
    // double red = rt->scene->ambi_light->rgb->r/255.0;
    // double green = rt->scene->ambi_light->rgb->g/255.0;
    // double blue = rt->scene->ambi_light->rgb->b/255.0;
    double red = rt->scene->ambi_light->rgb->r;
    double green = rt->scene->ambi_light->rgb->g;
    double blue = rt->scene->ambi_light->rgb->b;
    // color = color_init2(red,green,blue);
    color = check_color_is_valid(color_init2(red,green,blue));
    return color;
}