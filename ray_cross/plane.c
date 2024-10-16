/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshida <kyoshida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:52:24 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/14 18:21:51 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_cross.h"
#include "../includes/color.h"

double	cross_ray_plane(t_object *object, t_vec3 dir, t_rt *rt)
{
	t_vec3	cam2pl;
	double	denominator;
	double	molecule;

	cam2pl = vec3_sub(*rt->scene->camera->view_point, *object->p_in_the_plane);
	denominator = (vec3_dot(vec3_mul(dir, -1), *object->normal_vec));
	if (denominator == 0)
		return (-1);
	molecule = vec3_dot(cam2pl, *object->normal_vec);
	return (molecule / denominator);
}

bool	judge_denominator(t_vec3 dir, t_camera *camera, t_object *object)
{
	double	denominator;

	if (camera)
		;
	denominator = -(vec3_dot(dir, *object->normal_vec));
	if (denominator < 0)
		return (true);
	else
		return (false);
}

void	draw_plane(t_rt *rt, double x, double y, t_object *nearest_obj)
{
	double	t;
	double	distance;
	t_vec3	cam_center;
	t_vec3	dir;

	if (rt->scene->camera->view_degree / 2 == 90.0)
		return ;
	distance = rt->width / 2 / (tan((rt->scene->camera->view_degree / 2)
				/ (180 * 3.14159265358979323846)));
	cam_center = vec3_mul(*rt->scene->camera->nr_vec, distance);
	dir = get_dir(rt, x, y, cam_center);
	t = cross_ray_plane(nearest_obj, dir, rt);
	if (judge_denominator(dir, rt->scene->camera, nearest_obj))
		*nearest_obj->normal_vec = vec3_mul(*nearest_obj->normal_vec, -1);
	if (t >= 0)
		my_mlx_pixel_put(rt, x, y, phong_calc(rt, dir, nearest_obj));
	else
		my_mlx_pixel_put(rt, x, y, 0x000000);
}

double	calc_pl_distance(t_object *object, t_vec3 dir, t_vec3 *source_point)
{
	t_vec3	cam2pl;
	double	denominator;
	double	molecule;

	cam2pl = vec3_sub(*source_point, *object->p_in_the_plane);
	denominator = (vec3_dot(vec3_mul(dir, -1), *object->normal_vec));
	if (denominator == 0)
		return (-1);
	molecule = vec3_dot(cam2pl, *object->normal_vec);
	return (molecule / denominator);
}
