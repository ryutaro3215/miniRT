/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:25:54 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/05 23:25:56 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/utils.h"

void	free_sphere(t_object *object)
{
	free(object->center);
	free(object->rgb);
	free(object);
}

void	free_plane(t_object *object)
{
	free(object->p_in_the_plane);
	free(object->normal_vec);
	free(object->rgb);
	free(object);
}

void	free_cylinder(t_object *object)
{
	free(object->center);
	free(object->axic_vec);
	free(object->rgb);
	free(object->normal_vec);
	free(object);
}

void	free_object(t_object *object)
{
	t_object	*tmp;

	while (object != NULL)
	{
		tmp = object->next;
		if (object->type == SPHERE)
			free_sphere(object);
		else if (object->type == PLANE)
			free_plane(object);
		else if (object->type == CYLINDER)
			free_cylinder(object);
		else
			;
		object = tmp;
	}
}

void	free_scene(t_scene *scene)
{
	int	i;
	t_object *tmp;

	i = 0;
	free_ambi(scene->ambi_light);
	free_camera(scene->camera);
	free_light(scene->light);
	free_object(scene->object);
}


