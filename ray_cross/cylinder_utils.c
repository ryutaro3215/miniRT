/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylider_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 01:03:31 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/09 01:16:58 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_cross.h"
#include "../includes/ray_cross.h"

double	calc_cy_d(t_object *obj, t_vec3 dir, t_vec3 *source_point)
{
	double	a;
	double	b;
	double	c;

	a = vec3_mag(vec3_cross(dir, *obj->axic_vec));
	a *= a;
	b = 2 * vec3_dot(vec3_cross(dir, *obj->axic_vec),
			vec3_cross(vec3_sub(*source_point, *obj->center), *obj->axic_vec));
	c = vec3_mag(vec3_cross(vec3_sub(*source_point,
					*obj->center),*obj->axic_vec));
	c = c * c - (obj->diameter / 2) * (obj->diameter / 2);
	return (b * b - 4 * a * c);
}

double	calc_cy_t(t_object *obj, t_vec3 dir, int flag, t_vec3 *source_point)
{
	double	a;
	double	b;
	double	c;
	double	d;

	a = vec3_mag(vec3_cross(dir, *obj->axic_vec));
	a *= a;
	b = 2 * vec3_dot(vec3_cross(dir, *obj->axic_vec),
			vec3_cross(vec3_sub(*source_point, *obj->center), *obj->axic_vec));
	c = vec3_mag(vec3_cross(vec3_sub(*source_point,
					*obj->center), *obj->axic_vec));
	c = c * c - (obj->diameter / 2) * (obj->diameter / 2);
	d = b * b - 4 * a * c;
	if (flag == 1)
		return ((-b + sqrt(d)) / (2 * a));
	return ((-b - sqrt(d)) / (2 * a));
}

t_vec3	*calc_cy_intersections(t_object *obj, t_vec3 dir, t_vec3 *source_point)
{
	double	d;
	t_vec3	*intersections;

	d = calc_cy_d(obj, dir, source_point);
	if (d < 0)
		return (NULL);
	intersections = (t_vec3 *)malloc(sizeof(t_vec3) * 2);
	if (intersections == NULL)
		return (NULL);
	intersections[0] = vec3_add(*source_point,
			vec3_mul(dir, calc_cy_t(obj, dir, 0, source_point)));
	intersections[1] = vec3_add(*source_point,
			vec3_mul(dir, calc_cy_t(obj, dir, 1, source_point)));
	return (intersections);
}
