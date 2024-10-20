/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshida <kyoshida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:43:22 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/20 13:54:28 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/init_data.h"
#include "../includes/utils.h"
#include "../includes/minirt.h"
#include "../includes/color.h"
#include <stddef.h>
#include <stdlib.h>

bool	check_cylinder_param(char **splited_line)
{
	bool	flag;

	flag = true;
	if (ft_2d_array_len(splited_line) != 6)
		return (false);
	if (is_vec3(splited_line[1]) == false)
		flag = false;
	if (is_vec3(splited_line[2]) == false)
		flag = false;
	if ((is_point_num(splited_line[3]) == false
			|| ft_atof(splited_line[3]) <= 0)
		|| (is_point_num(splited_line[4]) == false
			|| ft_atof(splited_line[4]) <= 0))
		flag = false;
	if (check_color_range(splited_line[5]) == false)
		flag = false;
	return (flag);
}

bool	get_cylinder(char **splited_line, t_scene *scene)
{
	t_object	*cylinder;

	if (check_cylinder_param(splited_line) == false)
		return (false);
	cylinder = init_object();
	if (!cylinder)
		return (false);
	cylinder->type = CYLINDER;
	cylinder->center = (t_vec3 *)malloc(sizeof(t_vec3));
	cylinder->axic_vec = (t_vec3 *)malloc(sizeof(t_vec3));
	cylinder->rgb = (t_rgb *)malloc(sizeof(t_rgb));
	cylinder->diameter = ft_atof(splited_line[3]);
	cylinder->height = ft_atof(splited_line[4]);
	cylinder->normal_vec = (t_vec3 *)malloc(sizeof(t_vec3));
	if (!cylinder->type || !cylinder->axic_vec || !cylinder->rgb
		|| !cylinder->normal_vec)
		return (false);
	set_vec3(splited_line[1], cylinder->center);
	set_vec3(splited_line[2], cylinder->axic_vec);
	set_rgb(splited_line[5], cylinder->rgb);
	cylinder->next = scene->object;
	scene->object = cylinder;
	return (true);
}
