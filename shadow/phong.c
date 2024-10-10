/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:32:07 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/10/10 19:00:35 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shadow.h"
#include "../includes/ray_cross.h"

t_rgb	check_color_is_valid(t_rgb a)
{
	if (a.r > 1.0)
		a.r = 1.0;
	if (a.r < 0.0)
		a.r = 0.0;
	if (a.g > 1.0)
		a.g = 1.0;
	if (a.g < 0.0)
		a.g = 0.0;
	if (a.b > 1.0)
		a.b = 1.0;
	if (a.b < 0.0)
		a.b = 0.0;
	return (a);
}

uint32_t	color2hex(t_rgb color)
{
	return (color_ans(color.r * 255, color.g * 255, color.b * 255));
}
// 拡散反射光の計算

// 法線ベクトルの取得
t_vec3	get_normal(t_object *nearest_obj, t_vec3 intersection)
{
	if (nearest_obj->type == SPHERE)
		return (vec3_norm(vec3_sub(intersection, *nearest_obj->center)));
	else
		return (*nearest_obj->normal_vec);
}

// phong_calc 関数
int	phong_calc(t_rt *rt, t_vec3 dir_vec, t_object *nearest_obj)
{
	t_vec3	intersection;
	t_vec3	normal;
	t_vec3	light_vec;
	t_rgb	diff;
	t_rgb	spec;

	intersection = vec3_add(*rt->scene->camera->view_point,
			vec3_mul(dir_vec, calc_distance(nearest_obj, dir_vec,
					rt->scene->camera->view_point)));
	normal = get_normal(nearest_obj, intersection);
	light_vec = vec3_norm(vec3_sub(*rt->scene->light->light_point,
				intersection));
	diff = calc_diffuse(normal, light_vec, rt, nearest_obj);
	spec = calc_specular(normal, light_vec, dir_vec, rt);
	if (is_shadow(rt->scene, nearest_obj, dir_vec))
	{
		diff = color_init2(0.0, 0.0, 0.0);
		spec = color_init2(0.0, 0.0, 0.0);
	}
	return (color2hex(color_add(calc_ambient(rt, nearest_obj),
				color_add(diff, spec))));
}
