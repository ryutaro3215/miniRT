/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshida <kyoshida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:47:18 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/20 13:43:23 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/init_data.h"
#include "../includes/utils.h"
#include "../includes/minirt.h"
#include "../includes/color.h"
#include <stddef.h>
#include <stdlib.h>

bool	check_camera_param(char **splited_line)
{
	bool	flag;

	flag = true;
	if (ft_2d_array_len(splited_line) != 4)
		return (false);
	if (is_vec3(splited_line[1]) == false)
		flag = false;
	if (is_vec3(splited_line[2]) == false)
		flag = false;
	if (is_num(splited_line[3]) == false || ft_atoi(splited_line[3]) <= 0
		|| ft_atoi(splited_line[3]) >= 180)
		flag = false;
	return (flag);
}

bool	get_camera(char **splited_line, t_scene *scene)
{
	t_camera	*camera;

	if (check_camera_param(splited_line) == false)
		return (false);
	if (scene->camera != NULL)
		return (false);
	camera = (t_camera *)malloc(sizeof(t_camera));
	if (camera == NULL)
		return (false);
	camera->view_point = (t_vec3 *)malloc(sizeof(t_vec3));
	camera->nr_vec = (t_vec3 *)malloc(sizeof(t_vec3));
	if (camera->nr_vec == NULL || camera->view_point == NULL)
		return (false);
	set_vec3(splited_line[1], camera->view_point);
	set_vec3(splited_line[2], camera->nr_vec);
	camera->view_degree = ft_atoi(splited_line[3]);
	scene->camera = camera;
	return (true);
}
