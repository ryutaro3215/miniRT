/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:23:25 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/09/21 11:16:30 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/color.h"
#include "../includes/minirt.h"
#include "../includes/utils.h"

bool	check_color_range(char *rgb)
{
	bool	flag;

	flag = true;
	char **splited_rgb = ft_split(rgb, ',');
	if (ft_2d_array_len(splited_rgb) != 3)
		flag = false;
	if (is_num(splited_rgb[0]) == false || is_num(splited_rgb[1]) == false
			|| is_num(splited_rgb[2]) == false)
		flag = false;
	if ((ft_atoi(splited_rgb[0]) < 0 || ft_atoi(splited_rgb[0]) > 255)
			|| (ft_atoi(splited_rgb[1]) < 0 || ft_atoi(splited_rgb[1]) > 255)
			|| (ft_atoi(splited_rgb[2]) < 0 || ft_atoi(splited_rgb[2]) > 255))
		flag = false;
	ft_free_2d_array(splited_rgb);
	return (flag);
}

bool	check_color(int color)
{
	if (color < 0 || color > 255)
		return (false);
	return (true);
}

unsigned int	get_color(char *str)
{
	unsigned int	color;
	
	color = ft_atoi(str);
	if (!check_color(color))
		return (300);
	return (color);
}

void	set_rgb(char *str, t_rgb *rgb)
{
	char	**str_rgb;

	str_rgb = ft_split(str, ',');
	rgb->r = get_color(str_rgb[0])<<16;
	rgb->g = get_color(str_rgb[1])<<8;
	rgb->b = get_color(str_rgb[2]);
}

unsigned int	int_to_hex_color(t_rgb *rgb)
{
	unsigned int	color;

	color = 0;
	color += rgb->r;
	color = color << 8;
	color += rgb->g;
	color = color << 8;
	color += rgb->b;
	return (color);
}
