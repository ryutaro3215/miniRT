/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:30:07 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/08/01 15:20:33 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/minirt.h"
# include "includes/init_data.h"
# include "includes/check_file.h"
# include "includes/utils.h"
# include "includes/hook.h"

void	my_mlx_pixel_put(t_rt *rt, int x, int y, int color)
{
	char	*dst;

	dst = rt->addr + (y * rt->line_len + x * (rt->bpp / 8));
	*(unsigned int *)dst = color;
}
t_vec3 vec3_scale(t_vec3 v, double s) {
    return vec3_init(v.x * s, v.y * s, v.z * s);
}

t_vec3 vec3_reflect(t_vec3 v, t_vec3 n) {
    double dot = vec3_dot(v, n);
    return vec3_sub(vec3_scale(n, 2 * dot), v);
}
void	print_sphere(t_rt *rt)
{
	t_scene	*scene = rt->scene;
    double diffuse_strength = 0.8;
    double specular_strength = 0.5;
     int shininess = 32;
	for (double y = 0;  y < rt->height; ++y)
	{
		for (double x = 0; x < rt->width; ++x)
		{
			t_vec3	screen_vec;
			t_vec3	dir_vec;
			t_vec3	camera2sphere_vec;
			screen_vec = vec3_init(2 * x / rt->width - 1.0, 2 * y / rt->height - 1.0, 0);
			dir_vec = vec3_norm(vec3_sub(screen_vec, *scene->camera->view_point));
			camera2sphere_vec = vec3_sub(*scene->camera->view_point, *scene->sphere->center);
			double a = vec3_mag(dir_vec) * vec3_mag(dir_vec);
			double b = 2 * vec3_dot(camera2sphere_vec, dir_vec);
			double c = vec3_dot(camera2sphere_vec, camera2sphere_vec) - scene->sphere->diameter * scene->sphere->diameter;
			double d = b * b - 4 * a * c;
			if (d >= 0)
            {
                double t = (-b + sqrt(d)) / (2.0 * a);
                t_vec3 intersection = vec3_add(*scene->camera->view_point, vec3_scale(dir_vec, t));
                t_vec3 normal = vec3_norm(vec3_sub(intersection, *scene->sphere->center));
                t_vec3 light_vec = vec3_norm(vec3_sub(*scene->light->light_point, intersection));
                t_vec3 view_vec = vec3_norm(vec3_sub(*scene->camera->view_point, intersection));
                t_vec3 reflect_vec = vec3_reflect(vec3_scale(light_vec, -1), normal);

                double diff = fmax(vec3_dot(normal, light_vec), 0.0) * diffuse_strength;

                double spec = pow(fmax(vec3_dot(view_vec, reflect_vec), 0.0), shininess) * specular_strength;

                double brightness = scene->ambi_light->ratio + diff + spec;
                int r = (int)(fmin(scene->sphere->rgb->r * brightness , 1.0) * 255);
                int g = (int)(fmin(scene->sphere->rgb->g * brightness , 1.0) * 255);
                int b = (int)(fmin(scene->sphere->rgb->b * brightness , 1.0) * 255);

                int color = (r << 16) | (g << 8) | b;
                my_mlx_pixel_put(rt, x, y, color);
            }
			else
				my_mlx_pixel_put(rt, x, y, 0x00000000);
		}
	}
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
	 print_sphere(rt); 
	// print_plane(rt);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
	hook_event(rt);
	mlx_loop(rt->mlx);
	system("leaks minirt");
	return (0);
}
