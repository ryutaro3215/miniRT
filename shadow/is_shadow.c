/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:36:45 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/10/10 18:51:36 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shadow.h"
#include "../includes/ray_cross.h"

t_vec3	get_p(t_scene *scene, t_vec3 dir_vec, t_object *nearest_obj)
{
	double	t;
	t_vec3	p;

	t = calc_distance(nearest_obj, dir_vec, scene->camera->view_point);
	p = vec3_add(*scene->camera->view_point, vec3_mul(dir_vec, t));
	return (p);
}

t_vec3	get_intersec2light(t_scene *scene,
		t_vec3 dir_vec, t_object *nearest_obj)
{
	double	t;
	t_vec3	p;
	t_vec3	intersec2light;

	t = calc_distance(nearest_obj, dir_vec, scene->camera->view_point);
	p = get_p(scene, dir_vec, nearest_obj);
	intersec2light = vec3_sub(*scene->light->light_point, p);
	return (intersec2light);
}

t_vec3	get_l(t_scene *scene, t_object *nearest_obj, t_vec3 dir_vec)
{
	t_vec3		l;

	l = vec3_norm(get_intersec2light(scene, dir_vec, nearest_obj));
	return (l);
}

bool	is_shadow(t_scene *scene, t_object *nearest_obj, t_vec3 dir_vec)
{
	t_vec3		start;
	double		light_dist;
	t_vec3		dir;
	t_object	*object;
	double		distance;

	start = vec3_add(get_p(scene, dir_vec, nearest_obj),
			vec3_mul(get_l(scene, nearest_obj, dir_vec), 0.0001));
	light_dist = vec3_mag(get_intersec2light(scene, dir_vec, nearest_obj))
		- 0.0001;
	dir = vec3_norm(vec3_sub(*scene->light->light_point, start));
	object = scene->object;
	distance = calc_distance(object, dir, &start);
	while (object)
	{
		distance = calc_distance(object, dir, &start);
		if (distance >= 0 && distance <= light_dist)
			return (true);
		object = object->next;
	}
	return (false);
}
