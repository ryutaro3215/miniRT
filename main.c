/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshida <kyoshida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:30:07 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/20 13:29:51 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include "includes/init_data.h"
#include "includes/check_file.h"
#include "includes/utils.h"
#include "includes/hook.h"
#include "includes/ray_cross.h"
#include "includes/utils.h"

void	my_mlx_pixel_put(t_rt *rt, int x, int y, int color)
{
	char	*dst;

	dst = rt->addr + (y * rt->line_len + x * (rt->bpp / 8));
	*(unsigned int *)dst = color;
}

int	main(int argc, char **argv)
{
	t_rt		*rt;
	t_object	*head;

	if (argc != 2 || !check_file(argv[1]))
	{
		ft_printf("Invalid file or argument number is invalid.\n");
		return (1);
	}
	rt = make_data_structure();
	if (!rt)
		return (1);
	rt->scene = parse_file(argv[1], init_scene());
	if (rt->scene == NULL)
		return (free_env(rt), printf("Error\n"), 1);
	head = rt->scene->object;
	rt->scene->object = head;
	draw_object(rt);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
	hook_event(rt);
	mlx_loop(rt->mlx);
	free_env(rt);
	return (0);
}
