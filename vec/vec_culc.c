/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_culc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:29:27 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/08/13 17:02:17 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minirt.h"
# include "../libft/includes/libft.h"
# include "../includes/utils.h"

t_vec3	vec3_init(double x, double y, double z)
{
	t_vec3	vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	vec;
	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	return (vec);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	vec;
	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	vec.z = a.z - b.z;
	return (vec);
}

t_vec3	vec3_mul(t_vec3 a, double b)
{
	t_vec3	vec;
	vec.x = a.x * b;
	vec.y = a.y * b;
	vec.z = a.z * b;
	return (vec);
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	double	dot;

	dot = a.x * b.x + a.y * b.y + a.z * b.z;
	return (dot);
}	

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	vec;
	vec.x = a.y * b.z - a.z * b.y;
	vec.y = a.z * b.x - a.x * b.z;
	vec.z = a.x * b.y - a.y * b.x;
	return (vec);
}

double	vec3_mag(t_vec3 a)
{
	double	mag;

	mag = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (mag);
}

t_vec3	vec3_norm(t_vec3 a)
{
	double	mag;
    //0除算を防ぐ処理必要
	mag = 1 / vec3_mag(a);
	return (vec3_mul(a, mag));
}

void	set_vec3(char *str, t_vec3 *vec)
{
	char	**splited_line;

	splited_line = ft_split(str, ',');
	vec->x = ft_atof(splited_line[0]);
	vec->y = ft_atof(splited_line[1]);
	vec->z = ft_atof(splited_line[2]);
	ft_free_2d_array(splited_line);
}

bool	is_vec3(char *str)
{
	char	**splited_line;
	bool	flag;

	flag = true;
	splited_line = ft_split(str, ',');
	if (ft_2d_array_len(splited_line) != 3)
		flag = false;
	if (is_point_num(splited_line[0]) == false)
		flag = false;
	if (is_point_num(splited_line[1]) == false)
		flag = false;
	if (is_point_num(splited_line[2]) == false)
		flag = false;
	ft_free_2d_array(splited_line);
	return (flag);
}

bool	is_normal_vec3(char *str)
{
	char	**splited_line;
	bool	flag;
	t_vec3	vec;

	flag = true;
	splited_line = ft_split(str, ',');
	set_vec3(str, &vec);
	if (vec3_mag(vec) != 1.0f)
		flag = false;
	ft_free_2d_array(splited_line);
	return (flag);
}

t_vec3 vec3_reflect(t_vec3 v, t_vec3 n) {
    double dot = vec3_dot(v, n);
    return vec3_sub(vec3_mul(n, 2 * dot), v);
}
