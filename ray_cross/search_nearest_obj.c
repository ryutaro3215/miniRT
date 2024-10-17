/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_nearest_obj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshida <kyoshida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:07:03 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/17 15:23:06 by kyoshida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_cross.h"

double	calc_distance(t_object *obj, t_vec3 dir, t_vec3 *source_point)
{
	if (obj->type == SPHERE)
		return (calc_sp_distance(obj, dir, source_point));
	else if (obj->type == PLANE)
		return (calc_pl_distance(obj, dir, source_point));
	else if (obj->type == CYLINDER)
		return (calc_cy_distance(obj, dir, source_point));
	return (0);
}

t_object	*calc_obj_distance(t_vec3 dir, t_rt *rt)
{
	double		distance;
	double		min_distance;
	t_object	*nearest_obj;
	t_object	*tmp;

	min_distance = DISTANCE_MAX;
	tmp = rt->scene->object;
	nearest_obj = tmp;
	while (tmp)
	{
		distance = calc_distance(tmp, dir,
				rt->scene->camera->view_point);
		if (distance < 0)
		{
			tmp = tmp->next;
			continue ;
		}
		if (distance < min_distance)
		{
			min_distance = distance;
			nearest_obj = tmp;
		}
		tmp = tmp->next;
	}
	return (nearest_obj);
}

t_object	*search_nearest_obj(t_rt *rt, double x, double y)
{
	double		d;
	t_vec3		cam_center;
	t_vec3		dir;

	if (rt->scene->camera->view_degree / 2 == 90.0)
		return (NULL);
	d = rt->width / 2 / tan((rt->scene->camera->view_degree / 2)
			/ (180 * M_PI));
	cam_center = vec3_mul(*rt->scene->camera->nr_vec, d);
	dir = get_dir(rt, x, y, cam_center);
	return (calc_obj_distance(dir, rt));
}
