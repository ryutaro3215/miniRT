/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:30:07 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/08/08 20:34:27 by yoshidakazu      ###   ########.fr       */
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

void	print_plane(t_rt *rt)
{
	t_vec3	dir_vec = *rt->scene->camera->nr_vec;
	t_vec3	n_vec = *rt->scene->plane->normal_vec;
	t_vec3	view_p = *rt->scene->camera->view_point;
	t_vec3	p_vec = *rt->scene->plane->p_in_the_plane;
	double bunbo = -(vec3_dot(dir_vec, n_vec));
	if (bunbo == 0)
		my_mlx_pixel_put(rt, 0, 0, 0xffffff);
	double bunshi = vec3_dot(vec3_sub(view_p, p_vec), n_vec);
	double t = bunshi / bunbo;
	if (t >= 0)
		my_mlx_pixel_put(rt, 0, 0, 0x000000);
	else
		my_mlx_pixel_put(rt, 0, 0, 0xffffff);
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
	//  draw_plane(rt); 
    draw_object(rt);
	// draw_cylinder(rt);
	//  draw_sphere(rt); 
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
	hook_event(rt);
	mlx_loop(rt->mlx);
	system("leaks minirt");
	return (0);
}
