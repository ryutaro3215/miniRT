/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_calc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:08:27 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/10/10 19:05:37 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shadow.h"
#include "../includes/ray_cross.h"

t_rgb	calc_diffuse( t_vec3 normal, t_vec3 light_vec,
		t_rt *rt, t_object *nearest_obj)
{
	double	diff_deg;
	t_rgb	obj_color;
	t_rgb	light_color;

	light_color = get_light_color(rt);
	obj_color = nearest_objs_color(nearest_obj);
	diff_deg = vec3_dot(normal, light_vec);
	if (diff_deg < 0)
		diff_deg = 0;
	return (color_mul_scalar(color_mul(obj_color,
				color_mul_scalar(light_color,
					rt->scene->light->bright_ratio)), diff_deg));
}

// 鏡面反射の計算
t_rgb	calc_specular(t_vec3 normal, t_vec3 light_vec, t_vec3 dir_vec, t_rt *rt)
{
	t_vec3	v;
	t_vec3	r;
	t_rgb	light_color;
	double	spec_deg;

	light_color = get_light_color(rt);
	v = vec3_mul(dir_vec, -1);
	r = vec3_sub(vec3_mul(vec3_mul(normal,
					vec3_dot(normal, light_vec)), 2), light_vec);
	spec_deg = vec3_dot(v, r);
	if (spec_deg < 0)
		return (color_init2(0.0, 0.0, 0.0));
	return (color_mul_scalar(color_mul(rt->scene->light->factor->ks,
				color_mul_scalar(light_color, rt->scene->light->bright_ratio)),
			pow(spec_deg, rt->scene->light->factor->shininess)));
}

// アンビエント光の計算
t_rgb	calc_ambient(t_rt *rt, t_object *nearest_obj)
{
	t_rgb	obj_color;

	obj_color = nearest_objs_color(nearest_obj);
	return (color_mul(obj_color, color_mul_scalar(get_ambi_light_color(rt),
				rt->scene->ambi_light->ratio)));
}
