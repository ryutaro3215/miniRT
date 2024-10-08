/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:43:13 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/09 00:46:40 by rmatsuba         ###   ########.fr       */
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

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_rgb
{
	double	r;
	double	g;
	double	b;
}			t_rgb;

typedef struct s_ambi_light
{
	float	ratio;
	t_rgb	*rgb;
}			t_ambi_light;

typedef struct s_camera
{
	t_vec3	*view_point;
	t_vec3	*nr_vec;
	int		view_degree;
}			t_camera;

typedef struct s_factor
{
	t_rgb	ka;
	t_rgb	kd;
	t_rgb	ks;
	int		shininess;
}	t_factor;

typedef struct s_light
{
	t_vec3		*light_point;
	float		bright_ratio;
	t_rgb		*rgb;
	t_factor	*factor;
}			t_light;

// typedef struct	s_sphere
// {
// 	t_vec3	*center;
// 	float	diameter;
// 	t_rgb	*rgb;
// }		t_sphere;

// typedef struct	s_plane
// {
// 	t_vec3	*p_in_the_plane;
// 	t_vec3	*normal_vec;
// 	t_rgb	*rgb;
// }		t_plane;

// typedef struct	s_cylinder
// {
// 	t_vec3	*cylinder_center;
// 	t_vec3	*axic_vec;
// 	t_rgb	*rgb;
// 	float	diameter;
// 	float	height;
// }		t_cylinder;

enum e_object_type
{
	AMBIENT_LIGHT = 1,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
};

typedef struct s_object
{
	int				type;
	t_vec3			*center;
	t_vec3			*p_in_the_plane;
	t_vec3			*axic_vec;
	t_vec3			*normal_vec;
	float			diameter;
	float			height;
	t_rgb			*rgb;
	struct s_object	*next;
}		t_object;

typedef struct s_scene
{
	t_ambi_light	*ambi_light;
	t_camera		*camera;
	t_light			*light;
	t_object		*object;
}		t_scene;

typedef struct s_rt
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

// #define AMBIENT_LIGHT 1
// #define CAMERA 2
// #define LIGHT 3
// #define SPHERE 4
// #define PLANE 5
// #define CYLINDER 6

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
bool	is_vec3(char *str);
bool	is_normal_vec3(char *str);
t_vec3	vec3_reflect(t_vec3 v, t_vec3 n);
//It is definition of drawing
void	my_mlx_pixel_put(t_rt *rt, int x, int y, int color);

#endif
