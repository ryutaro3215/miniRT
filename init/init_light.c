/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:45:44 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/09 17:46:40 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/init_data.h"
#include "../includes/utils.h"
#include "../includes/minirt.h"
#include "../includes/color.h"
#include <stddef.h>
#include <stdlib.h>

bool	check_ambi_param(char **splited_line)
{
	float	ratio;

	if (ft_2d_array_len(splited_line) != 3)
		return (false);
	if (is_point_num(splited_line[1]) == false)
		return (false);
	ratio = ft_atof(splited_line[1]);
	if (ratio < 0.0f || ratio > 1.0f)
		return (false);
	if (check_color_range(splited_line[2]) == false)
		return (false);
	return (true);
}

bool	get_ambi_light(char **splited_line, t_scene *scene)
{
	t_ambi_light	*ambi_light;

	if (check_ambi_param(splited_line) == false)
		return (false);
	ambi_light = (t_ambi_light *)malloc(sizeof(t_ambi_light));
	ambi_light->ratio = ft_atof(splited_line[1]);
	ambi_light->rgb = (t_rgb *)malloc(sizeof(t_rgb));
	set_rgb(splited_line[2], ambi_light->rgb);
	scene->ambi_light = ambi_light;
	return (true);
}

bool	check_light_param(char **splited_line)
{
	bool	flag;

	flag = true;
	if (ft_2d_array_len(splited_line) != 4)
		return (false);
	if (is_vec3(splited_line[1]) == false)
		flag = false;
	if (is_point_num(splited_line[2]) == false
		|| ft_atof(splited_line[2]) < 0.0f || ft_atof(splited_line[2]) > 1.0f)
		flag = false;
	if (check_color_range(splited_line[3]) == false)
		flag = false;
	return (flag);
}

t_rgb	color_init(double r, double g, double b)
{
	t_rgb	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

bool	get_light(char **splited_line, t_scene *scene)
{
	t_light	*light;

	if (check_light_param(splited_line) == false)
		return (false);
	light = (t_light *)malloc(sizeof(t_light));
	light->light_point = (t_vec3 *)malloc(sizeof(t_vec3));
	light->rgb = (t_rgb *)malloc(sizeof(t_rgb));
	light->factor = (t_factor *)malloc(sizeof(t_factor));
	set_vec3(splited_line[1], light->light_point);
	set_rgb(splited_line[3], light->rgb);
	light->bright_ratio = ft_atof(splited_line[2]);
	light->factor->ka = color_init(0.6, 0.6, 0.6);
	light->factor->kd = color_init(0.8, 0.8, 0.8);
	light->factor->ks = color_init(0.9, 0.9, 0.9);
	light->factor->shininess = 10;
	scene->light = light;
	return (true);
}
