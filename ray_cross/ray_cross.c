/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cross.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:23:33 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/09 01:24:42 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_cross.h"
#include "../includes/color.h"

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
