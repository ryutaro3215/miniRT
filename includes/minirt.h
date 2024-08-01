/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:43:13 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/08/01 23:41:22 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/includes/libft.h"

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct	s_rgb
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}			t_rgb;

typedef struct	s_ambi_light
{
	float	ratio;
	t_rgb	*rgb;
}			t_ambi_light;

typedef struct	s_camera
{
	t_vec3	*view_point;
	t_vec3	*nr_vec;
	int		view_degree;
}			t_camera;

typedef struct	s_light
{
	t_vec3	*light_point;
	float	bright_ratio;
	t_rgb	*rgb;
}			t_light;

typedef struct	s_sphere
{
	t_vec3	*center;
	float	diameter;
	t_rgb	*rgb;
}		t_sphere;

typedef struct	s_plane
{
	t_vec3	*p_in_the_plane;
	t_vec3	*normal_vec;
	t_rgb	*rgb;
}		t_plane;

typedef struct	s_cylinder
{
	t_vec3	*cylinder_center;
	t_vec3	*axic_vec;
	t_rgb	*rgb;
	float	diameter;
	float	height;
}		t_cylinder;

typedef struct	s_scene
{
	t_ambi_light	*ambi_light;
	t_camera		*camera;
	t_light			*light;
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
}		t_scene;

typedef	struct s_rt
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	t_scene	*scene;
}		t_rt;

// It is definition of culculation of 3D vector.
t_vec3	vec3_init(double x, double y, double z);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_mul(t_vec3 a, double b);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	vec3_mag(t_vec3 a);
t_vec3	vec3_norm(t_vec3 a);
void	set_vec3(char *str, t_vec3 *vec);

int phong_calc(t_scene *scene, double a, double b, double d, t_vec3 dir_vec);
//It is definition of helper.c

#endif
