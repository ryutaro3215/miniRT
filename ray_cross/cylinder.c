/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:44:34 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/09 00:57:44 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_cross.h"

t_vec3	*get_inter(t_rt *rt, t_vec3 dir, t_vec3 cam2cyl, t_object *object)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vec3	*intersections;

	a = vec3_dot(dir, dir) - pow(vec3_dot(dir, *object->axic_vec), 2);
	b = 2 * (vec3_dot(dir, cam2cyl) - vec3_dot(dir, *object->axic_vec)
			* vec3_dot(*object->axic_vec, cam2cyl));
	c = vec3_dot(cam2cyl, cam2cyl) - pow(vec3_dot(*object->axic_vec,
				cam2cyl), 2) - object->diameter / 2 * object->diameter / 2;
	d = b * b - 4 * a * c;
	if (d < 0)
		return (NULL);
	intersections = (t_vec3 *)malloc(sizeof(t_vec3) * 2);
	if (intersections == NULL)
		return (NULL);
	intersections[0] = vec3_add(*rt->scene->camera->view_point,
			vec3_mul(dir, ((-b - sqrt(d)) / (2 * a))));
	intersections[1] = vec3_add(*rt->scene->camera->view_point,
			vec3_mul(dir, ((-b + sqrt(d)) / (2 * a))));
	return (intersections);
}

bool	judge_inner_outer(t_object *object, t_vec3 *center_set, double *h_set)
{
	bool	flag;
	t_vec3	projection_on_axis_outer;
	t_vec3	projection_on_axis_inner;

	if (h_set[1] >= 0 && h_set[1] <= object->height)
	{
		flag = true;
		projection_on_axis_outer = vec3_mul(*object->axic_vec, h_set[1]);
		*object->normal_vec = vec3_norm(vec3_sub(center_set[1],
					projection_on_axis_outer));
	}
	else if (h_set[0] >= 0 && h_set[0] <= object->height)
	{
		flag = true;
		projection_on_axis_inner = vec3_mul(*object->axic_vec, h_set[0]);
		*object->normal_vec = vec3_norm(
				vec3_sub(projection_on_axis_inner, center_set[0]));
	}
	else
		flag = false;
	return (flag);
}

//inner 0, outer 1

bool	discriminant_cylinder(t_rt *rt, t_vec3 dir, t_object *object)
{
	t_vec3	cam2cyl;
	t_vec3	*intersections;
	t_vec3	center_set[2];
	double	h_set[2];
	bool	flag;

	cam2cyl = vec3_sub(*rt->scene->camera->view_point, *object->center);
	intersections = get_inter(rt, dir, cam2cyl, object);
	if (intersections == NULL)
		return (false);
	center_set[0] = vec3_sub(intersections[1],*object->center);
	center_set[1] = vec3_sub(intersections[0],*object->center);
	h_set[0] = vec3_dot(center_set[0], *object->axic_vec);
	h_set[1] = vec3_dot(center_set[1], *object->axic_vec);
	flag = judge_inner_outer(object, center_set, h_set);
	free(intersections);
	return (flag);
}

void	draw_cylinder(t_rt *rt, double x, double y, t_object *nearest_obj)
{
	bool	is_drawable;
	double	d1;
	t_vec3	dir;
	t_vec3	cam_center;

	d1 = rt->width / 2 / tan((rt->scene->camera->view_degree / 2)
			/ (180 * 3.14159265358979323846));
	cam_center = vec3_mul(*rt->scene->camera->nr_vec, d1);
	dir = get_dir(rt, x, y, cam_center);
	is_drawable = discriminant_cylinder(rt, dir, nearest_obj);
	if (is_drawable == true)
		my_mlx_pixel_put(rt, x, y, phong_calc(rt, dir, nearest_obj));
	else
		my_mlx_pixel_put(rt, x, y, 0x000000);
}

double	calc_cy_distance(t_object *object, t_vec3 dir, t_vec3 *source_point)
{
	t_vec3	*intersections;
	double	h_outer;
	double	h_inner;
	double	distance;

	intersections = calc_cy_intersections(object, dir, source_point);
	if (intersections == NULL)
		return (-1);
	h_outer = vec3_dot(vec3_sub(intersections[0],
				*object->center), *object->axic_vec);
	h_inner = vec3_dot(vec3_sub(intersections[1],
				*object->center), *object->axic_vec);
	if (h_outer >= 0 && h_outer <= object->height)
		distance = calc_cy_t(object, dir, 0, source_point);
	else if (h_inner >= 0 && h_inner <= object->height)
		distance = calc_cy_t(object, dir, 1, source_point);
	else
		distance = -1;
	free(intersections);
	return (distance);
}
