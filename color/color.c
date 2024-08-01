/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:23:25 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/08/01 20:52:57 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/color.h"
#include "../includes/minirt.h"
#include "../includes/utils.h"

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
		return (0);
	return (color);
}

void	set_rgb(char *str, t_rgb *rgb)
{
	char	**str_rgb;

	str_rgb = ft_split(str, ',');
	rgb->r = get_color(str_rgb[0]);
	rgb->g = get_color(str_rgb[1]);
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
