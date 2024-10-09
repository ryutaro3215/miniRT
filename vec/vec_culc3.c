/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_culc3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:08:27 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/09 18:08:49 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../libft/includes/libft.h"
#include "../includes/utils.h"

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	vec;

	vec.x = a.y * b.z - a.z * b.y;
	vec.y = a.z * b.x - a.x * b.z;
	vec.z = a.x * b.y - a.y * b.x;
	return (vec);
}

double	vec3_mag(t_vec3 a)
{
	double	mag;

	mag = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (mag);
}

t_vec3	vec3_norm(t_vec3 a)
{
	double	mag;
	double	eps;

	eps = 1e-10;
	if (vec3_mag(a) < eps)
		return (a);
	mag = 1 / vec3_mag(a);
	return (vec3_mul(a, mag));
}
