/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_culc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:29:27 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/08/01 16:03:17 by yoshidakazu      ###   ########.fr       */
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
