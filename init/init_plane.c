/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshida <kyoshida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:42:34 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/20 13:55:35 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/init_data.h"
#include "../includes/utils.h"
#include "../includes/minirt.h"
#include "../includes/color.h"
#include <stddef.h>
#include <stdlib.h>

bool	check_plane_param(char **splited_line)
{
	bool	flag;

	flag = true;
	if (ft_2d_array_len(splited_line) != 4)
		return (false);
	if (is_vec3(splited_line[1]) == false)
		flag = false;
	if (is_vec3(splited_line[2]) == false)
		flag = false;
	if (check_color_range(splited_line[3]) == false)
		flag = false;
	return (flag);
}

bool	get_plane(char **splited_line, t_scene *scene)
{
	t_object	*plane;

	if (check_plane_param(splited_line) == false)
		return (false);
	plane = init_object();
	if (!plane)
		return (false);
	plane->type = PLANE;
	plane->p_in_the_plane = (t_vec3 *)malloc(sizeof(t_vec3));
	plane->normal_vec = (t_vec3 *)malloc(sizeof(t_vec3));
	plane->rgb = (t_rgb *)malloc(sizeof(t_rgb));
	if (!plane->p_in_the_plane || !plane->normal_vec || !plane->rgb)
		return (false);
	set_vec3(splited_line[1], plane->p_in_the_plane);
	set_vec3(splited_line[2], plane->normal_vec);
	set_rgb(splited_line[3], plane->rgb);
	plane->next = scene->object;
	scene->object = plane;
	return (true);
}
