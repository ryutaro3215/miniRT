/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:40:39 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/07/26 23:29:14 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/hook.h"
#include "../includes/utils.h"

int	close_win(t_rt *rt)
{
	mlx_destroy_image(rt->mlx, rt->img);
	mlx_destroy_window(rt->mlx, rt->mlx_win);
	mlx_destroy_display(rt->mlx);
	free(rt->mlx);
	free_scene(rt->scene);
	free(rt);
	exit(0);
}

int	key_press(int keynum, t_rt *rt)
{
	if (keynum == ESC)
		close_win(rt);
	return (0);
}

void	hook_event(t_rt *rt)
{
	mlx_hook(rt->mlx_win, 17, 0, close_win, rt);
	mlx_key_hook(rt->mlx_win, key_press, rt);
}
