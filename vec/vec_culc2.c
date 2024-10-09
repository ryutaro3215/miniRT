/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_culc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:07:19 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/09 18:07:55 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../libft/includes/libft.h"
#include "../includes/utils.h"

t_vec3	vec3_init(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	return (vec);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	vec;

	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	vec.z = a.z - b.z;
	return (vec);
}

t_vec3	vec3_mul(t_vec3 a, double b)
{
	t_vec3	vec;

	vec.x = a.x * b;
	vec.y = a.y * b;
	vec.z = a.z * b;
	return (vec);
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	double	dot;

	dot = a.x * b.x + a.y * b.y + a.z * b.z;
	return (dot);
}
