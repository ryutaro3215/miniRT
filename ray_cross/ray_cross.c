/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cross.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshida <kyoshida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:23:33 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/10 19:52:35 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_cross.h"
#include "../includes/color.h"

void	cam_is_valid(t_rt *rt, t_vec3 *esx, t_vec3 *esy)
{
	if (rt->scene->camera->nr_vec->x == 0 && rt->scene->camera->nr_vec->y != 0
		&& rt->scene->camera->nr_vec->z == 0)
	{
		if (rt->scene->camera->nr_vec->y > 0)
		{
			*esx = vec3_init(-1, 0, 0);
			*esy = vec3_init(0, 0, -1);
		}
		else
		{
			*esx = vec3_init(1, 0, 0);
			*esy = vec3_init(0, 0, 1);
		}
	}
}

t_vec3	get_dir(t_rt *rt, double x, double y, t_vec3 cam_center)
{
	t_vec3	esx;
	t_vec3	esy;
	t_vec3	xx;
	t_vec3	yy;
	t_vec3	dir;

	esx.x = cam_center.z
		/ sqrt(cam_center.z * cam_center.z + cam_center.x * cam_center.x);
	esx.y = 0;
	esx.z = -cam_center.x
		/ sqrt(cam_center.z * cam_center.z + cam_center.x * cam_center.x);
	esy = vec3_norm(vec3_cross(vec3_mul(cam_center, -1), esx));
	cam_is_valid(rt, &esx, &esy);
	xx = vec3_mul(esx, x - (rt->width - 1) / 2);
	yy = vec3_mul(esy, (rt->height - 1) / 2 - y);
	dir = vec3_norm(vec3_add(cam_center, vec3_add(xx, yy)));
	return (dir);
}

void	draw_object(t_rt *rt)
{
	double		x;
	double		y;
	t_object	*nearest_obj;

	x = 0;
	y = 0;
	while (y < rt->height)
	{
		while (x < rt->width)
		{
			nearest_obj = NULL;
			nearest_obj = search_nearest_obj(rt, x, y);
			if (nearest_obj->type == SPHERE)
				draw_sphere(rt, x, y, nearest_obj);
			else if (nearest_obj->type == PLANE)
				draw_plane(rt, x, y, nearest_obj);
			else if (nearest_obj->type == CYLINDER)
				draw_cylinder(rt, x, y, nearest_obj);
			x++;
		}
		x = 0;
		y++;
	}
}
