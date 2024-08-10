/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:16:29 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/08/10 19:57:06 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"
#include "../includes/minirt.h"

bool	is_num(char *str)
{
	int	i;
	bool	flag;

	i = 0;
	flag = false;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		else
			break ;
	}
	if (str[i] == '\0')
		flag = true;
	return (flag);
}

bool	is_point_num(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0)
		return (false);
	if ((str[i] == '-' || str[i] == '+') && (str[i + 1] != '.' || str[i + 1] == '\0'))
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == '.' || (str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			return (false);
	}
	return (true);
}


void	free_ambi_light(t_ambi_light *ambi_light)
{
	free(ambi_light->rgb);
	free(ambi_light);
}

void	free_camera(t_camera *camera)
{
	free(camera->view_point);
	free(camera->nr_vec);
	free(camera);
}

void	free_light(t_light *light)
{
	free(light->light_point);
	free(light->rgb);
	free(light);
}

void	free_sphere(t_object *sphere)
{
	free(sphere->center);
	free(sphere->rgb);
	free(sphere);
}

void	free_plane(t_object *plane)
{
	free(plane->p_in_the_plane);
	free(plane->normal_vec);
	free(plane->rgb);
	free(plane);
}

void	free_cylinder(t_object *cylinder)
{
	free(cylinder->center);
	free(cylinder->axic_vec);
	free(cylinder->rgb);
	free(cylinder);
}

void	free_scene(t_scene *scene)
{
	if (scene->ambi_light)
		free_ambi_light(scene->ambi_light);
	if (scene->camera)
		free_camera(scene->camera);
	if (scene->light)
		free_light(scene->light);
	if (scene->object->type == SPHERE)
		free_sphere(scene->object);
	if (scene->object->type == PLANE)
		free_plane(scene->object);
	if (scene->object->type == CYLINDER)
		free_cylinder(scene->object);
	free(scene);
}

size_t	ft_2d_array_len(char **array)
{
	size_t	len;

	len = 0;
	while (array[len] != NULL)
		len++;
	return (len);
}

void	ft_free_2d_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	print_scene(t_scene *scene)
{
	if (scene->ambi_light != NULL)
	{
	printf("ambilight\n");
	printf("ratio: %f\n", scene->ambi_light->ratio);
	printf("rgb: %d %d %d\n", scene->ambi_light->rgb->r, 
			scene->ambi_light->rgb->g, scene->ambi_light->rgb->b);
	}
	printf("-----------------------------\n");
	if (scene->camera != NULL)
	{
		printf("camera\n");
		printf("view_point: %f %f %f\n", scene->camera->view_point->x,
				scene->camera->view_point->y, scene->camera->view_point->z);
		printf("nr_vec: %f %f %f\n", scene->camera->nr_vec->x,
				scene->camera->nr_vec->y, scene->camera->nr_vec->z);
		printf("view_degree: %d\n", scene->camera->view_degree);
	}
	printf("-----------------------------\n");
	if (scene->light != NULL)
	{
		printf("light\n");
		printf("light_point: %f %f %f\n", scene->light->light_point->x,
				scene->light->light_point->y, scene->light->light_point->z);
		printf("bright_ratio: %f\n", scene->light->bright_ratio);
		printf("rgb: %d %d %d\n", scene->light->rgb->r, scene->light->rgb->g,
				scene->light->rgb->b);
	}
	while (scene->object != NULL)
	{
		printf("object\n");
		printf("-----------------------------\n");
		if (scene->object->type == SPHERE)
		{
			printf("sphere\n");
			printf("center: %f %f %f\n", scene->object->center->x, scene->object->center->y, scene->object->center->z);
			printf("diameter: %f\n", scene->object->diameter);
			printf("rgb: %d %d %d\n", scene->object->rgb->r, scene->object->rgb->g, scene->object->rgb->b);
		}
		if (scene->object->type == PLANE)
		{
			printf("plane\n");
			printf("p_in_the_plane: %f %f %f\n", scene->object->p_in_the_plane->x, scene->object->p_in_the_plane->y, scene->object->p_in_the_plane->z);
			printf("normal_vec: %f %f %f\n", scene->object->normal_vec->x, scene->object->normal_vec->y, scene->object->normal_vec->z);
			printf("rgb: %d %d %d\n", scene->object->rgb->r, scene->object->rgb->g, scene->object->rgb->b);
		}
		if (scene->object->type == CYLINDER)
		{
			printf("cylinder\n");
			printf("center: %f %f %f\n", scene->object->center->x, scene->object->center->y, scene->object->center->z);
			printf("axic_vec: %f %f %f\n", scene->object->axic_vec->x, scene->object->axic_vec->y, scene->object->axic_vec->z);
			printf("diameter: %f\n", scene->object->diameter);
			printf("height: %f\n", scene->object->height);
			printf("rgb: %d %d %d\n", scene->object->rgb->r, scene->object->rgb->g, scene->object->rgb->b);
		}
		scene->object = scene->object->next;
	}
}
