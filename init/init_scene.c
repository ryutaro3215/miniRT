/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:49:26 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/09 17:50:13 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/init_data.h"
#include "../includes/utils.h"
#include "../includes/minirt.h"
#include "../includes/color.h"
#include <stddef.h>
#include <stdlib.h>

t_object	*init_object(void)
{
	t_object	*object;

	object = (t_object *)malloc(sizeof(t_object));
	object->type = 0;
	object->center = NULL;
	object->p_in_the_plane = NULL;
	object->normal_vec = NULL;
	object->axic_vec = NULL;
	object->rgb = NULL;
	object->diameter = 0;
	object->height = 0;
	object->next = NULL;
	return (object);
}

bool	get_object(char **splited_line, t_scene *scene)
{
	char	*attr;
	bool	flag;

	flag = true;
	attr = splited_line[0];
	if (ft_strncmp(attr, "sp", ft_strlen(attr)) == 0)
		flag = get_sphere(splited_line, scene);
	else if (ft_strncmp(attr, "pl", ft_strlen(attr)) == 0)
		flag = get_plane(splited_line, scene);
	else if (ft_strncmp(attr, "cy", ft_strlen(attr)) == 0)
		flag = get_cylinder(splited_line, scene);
	else
		flag = false;
	return (flag);
}

t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	scene->ambi_light = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->object = NULL;
	return (scene);
}
