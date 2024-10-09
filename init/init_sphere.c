/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:40:56 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/09 17:42:08 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/init_data.h"
#include "../includes/utils.h"
#include "../includes/minirt.h"
#include "../includes/color.h"
#include <stddef.h>
#include <stdlib.h>

bool	check_sphere_param(char **splited_line)
{
	bool	flag;

	flag = true;
	if (ft_2d_array_len(splited_line) != 4)
		return (false);
	if (is_vec3(splited_line[1]) == false)
		flag = false;
	if (is_point_num(splited_line[2]) == false || ft_atof(splited_line[2]) <= 0)
		flag = false;
	printf("splited_line[3]: %s\n", splited_line[3]);
	if (check_color_range(splited_line[3]) == false)
		flag = false;
	return (flag);
}

bool	get_sphere(char **splited_line, t_scene *scene)
{
	t_object	*sphere;

	if (check_sphere_param(splited_line) == false)
		return (false);
	sphere = init_object();
	sphere->type = SPHERE;
	sphere->center = (t_vec3 *)malloc(sizeof(t_vec3));
	sphere->rgb = (t_rgb *)malloc(sizeof(t_rgb));
	set_vec3(splited_line[1], sphere->center);
	set_rgb(splited_line[3], sphere->rgb);
	sphere->diameter = ft_atof(splited_line[2]);
	sphere->next = scene->object;
	scene->object = sphere;
	return (true);
}
