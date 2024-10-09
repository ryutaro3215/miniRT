/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_culc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:29:27 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/09 18:09:13 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../libft/includes/libft.h"
#include "../includes/utils.h"

void	set_vec3(char *str, t_vec3 *vec)
{
	char	**splited_line;

	splited_line = ft_split(str, ',');
	vec->x = ft_atof(splited_line[0]);
	vec->y = ft_atof(splited_line[1]);
	vec->z = ft_atof(splited_line[2]);
	ft_free_2d_array(splited_line);
}

bool	is_vec3(char *str)
{
	char	**splited_line;
	bool	flag;

	flag = true;
	splited_line = ft_split(str, ',');
	if (ft_2d_array_len(splited_line) != 3)
		flag = false;
	if (is_point_num(splited_line[0]) == false)
		flag = false;
	if (is_point_num(splited_line[1]) == false)
		flag = false;
	if (is_point_num(splited_line[2]) == false)
		flag = false;
	ft_free_2d_array(splited_line);
	return (flag);
}

bool	is_normal_vec3(char *str)
{
	char	**splited_line;
	bool	flag;
	t_vec3	vec;

	flag = true;
	splited_line = ft_split(str, ',');
	set_vec3(str, &vec);
	if (vec3_mag(vec) != 1.0f)
		flag = false;
	ft_free_2d_array(splited_line);
	return (flag);
}

t_vec3	vec3_reflect(t_vec3 v, t_vec3 n)
{
	double	dot;

	dot = vec3_dot(v, n);
	return (vec3_sub(vec3_mul(n, 2 * dot), v));
}
