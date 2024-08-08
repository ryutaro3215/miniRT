/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cross.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:23:33 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/08/08 00:20:10 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_cross.h"
#include "../includes/color.h"

double	discriminant(t_rt *rt, t_vec3 screen_vec)
{
	t_vec3	dir;
	t_vec3	cam2sph;
	double	a;
	double	b;
	double	c;

	dir = vec3_norm(vec3_sub(screen_vec, *rt->scene->camera->view_point));
	cam2sph = vec3_sub(*rt->scene->camera->view_point, *rt->scene->sphere->center);
	a = vec3_dot(dir, dir);
	b = 2 * vec3_dot(cam2sph, dir);
	c = vec3_dot(cam2sph, cam2sph) - (rt->scene->sphere->diameter * rt->scene->sphere->diameter);
	return (b * b - 4 * a * c);
}

void	draw_sphere(t_rt *rt)
{
	t_vec3	screen_vec;
	double	x;
	double	y;
	double	d;

	x = 0;
	y = 0;
	d = 0;
	while (y < rt->height)
	{
		while (x < rt->width)
		{
			screen_vec = vec3_init(2 * x / rt->width - 1.0, 2 * y / rt->height - 1.0, 0);
			d = discriminant(rt, screen_vec);
			if (d >= 0)
				my_mlx_pixel_put(rt, x, y, int_to_hex_color(rt->scene->sphere->rgb));
			else
				my_mlx_pixel_put(rt, x, y, 0x000000);
			x++;
		}
		x = 0;
		y++;
	}
}

double	cross_ray_plane(t_rt *rt, t_vec3 screen_vec)
{
	t_vec3	dir;
	t_vec3	cam2pl;
	double	denominator;
	double	molecule;

	dir = vec3_norm(vec3_sub(screen_vec, *rt->scene->camera->view_point)); 
	cam2pl = vec3_sub(*rt->scene->camera->view_point, *rt->scene->plane->p_in_the_plane);
	denominator = -(vec3_dot(dir, *rt->scene->plane->normal_vec));
	if (denominator == 0)
		return (-1);
	molecule = vec3_dot(cam2pl, *rt->scene->plane->normal_vec);
	return (molecule / denominator);
}

void	draw_plane(t_rt *rt)
{
	t_vec3	screen_vec;
	double	x;
	double	y;
	double	t;

	x = 0;
	y = 0;
	t = 0;
	while (y < rt->height)
	{
		while (x < rt->width)
		{
			screen_vec = vec3_init(2 * x / rt->width - 1.0, 2 * y / rt->height - 1.0, 0);
			t = cross_ray_plane(rt, screen_vec);
			if (t > 0)
				my_mlx_pixel_put(rt, x, y, int_to_hex_color(rt->scene->plane->rgb));
			else
				my_mlx_pixel_put(rt, x, y, 0x000000);
			x++;
		}
		x = 0;
		y++;
	}
}

double	discriminant_cylinder(t_rt *rt, t_vec3 screen_vec) 
{
	t_vec3	dir;
	t_vec3	cam2cyl;
	double	a;
	double	b;
	double	c;

	dir = vec3_norm(vec3_sub(screen_vec, *rt->scene->camera->view_point));
	cam2cyl = vec3_sub(*rt->scene->camera->view_point, *rt->scene->cylinder->cylinder_center);
	a = vec3_dot(dir, dir) - pow(vec3_dot(dir, *rt->scene->cylinder->axic_vec), 2);
	b = 2 * (vec3_dot(dir, cam2cyl) - vec3_dot(dir, *rt->scene->cylinder->axic_vec)
			* vec3_dot(*rt->scene->cylinder->axic_vec, cam2cyl));
	c = vec3_dot(cam2cyl, cam2cyl) - pow(vec3_dot(*rt->scene->cylinder->axic_vec, cam2cyl), 2)
		- rt->scene->cylinder->diameter / 2 * rt->scene->cylinder->diameter / 2;
	return (b * b - 4 * a * c);
}


void	draw_cylinder(t_rt *rt)
{
	t_vec3	screen_vec;
	double	x;
	double	y;
	double	d;

	x = 0;
	y = 0;
	d = 0;
	while (y < rt->height)
	{
		while (x < rt->width)
		{
			screen_vec = vec3_init(2 * x / rt->width - 1.0, 2 * y / rt->height - 1.0, 0);
			d = discriminant_cylinder(rt, screen_vec);
			if (d >= 0)
				my_mlx_pixel_put(rt, x, y, int_to_hex_color(rt->scene->cylinder->rgb));
			else
				my_mlx_pixel_put(rt, x, y, 0x000000);
			x++;
		}
		x = 0;
		y++;
	}
}
