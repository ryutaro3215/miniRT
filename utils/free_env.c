/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:21:23 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/20 13:25:16 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/utils.h"

void	free_ambi(t_ambi_light *ambi)
{
	if (ambi == NULL)
		return ;
	free(ambi->rgb);
	free(ambi);
}

void	free_camera(t_camera *camera)
{
	if (camera == NULL)
		return ;
	free(camera->view_point);
	free(camera->nr_vec);
	free(camera);
}

void	free_light(t_light *light)
{
	if (light == NULL)
		return ;
	free(light->factor);
	free(light->light_point);
	free(light->rgb);
	free(light);
}

void	free_env(t_rt *rt)
{
	mlx_destroy_image(rt->mlx, rt->img);
	mlx_destroy_window(rt->mlx, rt->mlx_win);
	free(rt->mlx);
	free_scene(rt->scene);
	free(rt);
}
