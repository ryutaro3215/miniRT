/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:30:07 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/08/10 21:47:23 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/minirt.h"
# include "includes/init_data.h"
# include "includes/check_file.h"
# include "includes/utils.h"
# include "includes/hook.h"
# include "includes/ray_cross.h"

void	my_mlx_pixel_put(t_rt *rt, int x, int y, int color)
{
	char	*dst;

	dst = rt->addr + (y * rt->line_len + x * (rt->bpp / 8));
	*(unsigned int *)dst = color;
}

int	main(int argc, char **argv)
{
	t_rt	*rt;
	t_scene	*scene;

	if (argc != 2 || !check_file(argv[1]))
	{
		ft_printf("Invalid file or argument number is invalid.\n");
		return (1);
	}
	rt = make_data_structure();
	scene = init_scene();
	scene = parse_file(argv[1], scene);
	rt->scene = scene;
	if (rt->scene == NULL)
		printf("Error\n");
	else
		print_scene(rt->scene);
	/* draw_plane(rt); */ 
	/* draw_object(rt); */
	/* draw_cylinder(rt); */
	/* draw_sphere(rt); */ 
	/* mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0); */
	/* hook_event(rt); */
	/* mlx_loop(rt->mlx); */
	/* system("leaks minirt"); */
	return (0);
}
