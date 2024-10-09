/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:53:22 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/09 00:42:53 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_cross.h"

double	discriminant(t_rt *rt, t_vec3 dir, t_object *object)
{
	t_vec3	cam2sph;
	double	a;
	double	b;
	double	c;

	cam2sph = vec3_sub(*rt->scene->camera->view_point, *object->center);
	a = vec3_dot(dir, dir);
	b = 2 * vec3_dot(cam2sph, dir);
	c = vec3_dot(cam2sph, cam2sph) - (object->diameter * object->diameter);
	return (b * b - 4 * a * c);
}

void	draw_sphere(t_rt *rt, double x, double y, t_object *nearest_obj)
{
	double	demoninator;
	double	distance;
	t_vec3	cam_center;
	t_vec3	dir;

	distance = rt->width / 2 / tan((rt->scene->camera->view_degree / 2)
			/ (180 * 3.14159265358979323846));
	cam_center = vec3_mul(*rt->scene->camera->nr_vec, distance);
	dir = get_dir(rt, x, y, cam_center);
	demoninator = 0;
	demoninator = discriminant(rt, dir, nearest_obj);
	if (demoninator >= 0)
		my_mlx_pixel_put(rt, x, y, phong_calc(rt, dir, nearest_obj));
	else
	{
		printf("d:%f\n", demoninator);
		my_mlx_pixel_put(rt, x, y, 0x000000);
	}
}

double	calc_sp_distance(t_object *object, t_vec3 dir, t_vec3 *source_point)
{
	t_vec3	sph2source;
	double	a;
	double	b;
	double	c;
	double	t;

	sph2source = vec3_sub(*source_point, *object->center);
	a = vec3_dot(dir, dir);
	b = 2 * vec3_dot(sph2source, dir);
	c = vec3_dot(sph2source, sph2source)
		- (object->diameter * object->diameter);
	if (b * b - 4 * a * c < 0)
		return (-1);
	t = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
	return (t);
}