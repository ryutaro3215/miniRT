/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:16:29 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/07/26 00:57:48 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"
#include "../includes/minirt.h"

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

void	free_sphere(t_sphere *sphere)
{
	free(sphere->center);
	free(sphere->rgb);
	free(sphere);
}

void	free_plane(t_plane *plane)
{
	free(plane->p_in_the_plane);
	free(plane->normal_vec);
	free(plane->rgb);
	free(plane);
}

void	free_cylinder(t_cylinder *cylinder)
{
	free(cylinder->cylinder_center);
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
	if (scene->sphere)
		free_sphere(scene->sphere);
	if (scene->plane)
		free_plane(scene->plane);
	if (scene->cylinder)
		free_cylinder(scene->cylinder);
	free(scene);
}

void	print_scene(t_scene *scene)
{
	printf("scene\n");
	printf("ambilight\n");
	printf("ratio: %f\n", scene->ambi_light->ratio);
	printf("rgb: %d %d %d\n", scene->ambi_light->rgb->r, scene->ambi_light->rgb->g, scene->ambi_light->rgb->b);
	printf("camera\n");
	printf("view_point: %f %f %f\n", scene->camera->view_point->x, scene->camera->view_point->y, scene->camera->view_point->z);
	printf("nr_vec: %f %f %f\n", scene->camera->nr_vec->x, scene->camera->nr_vec->y, scene->camera->nr_vec->z);
	printf("view_degree: %d\n", scene->camera->view_degree);
	printf("light\n");
	printf("light_point: %f %f %f\n", scene->light->light_point->x, scene->light->light_point->y, scene->light->light_point->z);
	printf("bright_ratio: %f\n", scene->light->bright_ratio);
	printf("rgb: %d %d %d\n", scene->light->rgb->r, scene->light->rgb->g, scene->light->rgb->b);
	printf("sphere\n");
	printf("center: %f %f %f\n", scene->sphere->center->x, scene->sphere->center->y, scene->sphere->center->z);
	printf("diameter: %f\n", scene->sphere->diameter);
	printf("rgb: %d %d %d\n", scene->sphere->rgb->r, scene->sphere->rgb->g, scene->sphere->rgb->b);
	printf("plane\n");
	printf("p_in_the_plane: %f %f %f\n", scene->plane->p_in_the_plane->x, scene->plane->p_in_the_plane->y, scene->plane->p_in_the_plane->z);
	printf("nr_vec: %f %f %f\n", scene->plane->normal_vec->x, scene->plane->normal_vec->y, scene->plane->normal_vec->z);
	printf("rgb: %d %d %d\n", scene->plane->rgb->r, scene->plane->rgb->g, scene->plane->rgb->b);
	printf("cylinder\n");
	printf("cylinder_center: %f %f %f\n", scene->cylinder->cylinder_center->x, scene->cylinder->cylinder_center->y, scene->cylinder->cylinder_center->z);
	printf("axis_vec: %f %f %f\n", scene->cylinder->axic_vec->x, scene->cylinder->axic_vec->y, scene->cylinder->axic_vec->z);
	printf("rgb: %d %d %d\n", scene->cylinder->rgb->r, scene->cylinder->rgb->g, scene->cylinder->rgb->b);
	printf("diameter: %f\n", scene->cylinder->diameter);
	printf("height: %f\n", scene->cylinder->height);
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
