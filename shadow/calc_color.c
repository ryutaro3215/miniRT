/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:07:11 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/10/10 18:28:10 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shadow.h"
#include "../includes/ray_cross.h"

t_rgb	nearest_objs_color(t_object *nearest_obj)
{
	t_rgb	color;
	double	red;
	double	green;
	double	blue;

	red = nearest_obj->rgb->r;
	green = nearest_obj->rgb->g;
	blue = nearest_obj->rgb->b;
	color = check_color_is_valid(color_init2(red, green, blue));
	return (color);
}

t_rgb	get_light_color(t_rt *rt)
{
	t_rgb	color;
	double	red;
	double	green;
	double	blue;

	red = rt->scene->light->rgb->r;
	green = rt->scene->light->rgb->g;
	blue = rt->scene->light->rgb->b;
	color = check_color_is_valid(color_init2(red, green, blue));
	return (color);
}

t_rgb	get_ambi_light_color(t_rt *rt)
{
	t_rgb	color;
	double	red;
	double	green;
	double	blue;

	red = rt->scene->ambi_light->rgb->r;
	green = rt->scene->ambi_light->rgb->g;
	blue = rt->scene->ambi_light->rgb->b;
	color = check_color_is_valid(color_init2(red, green, blue));
	return (color);
}
