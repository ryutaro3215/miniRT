/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:16:35 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/09/21 12:56:31 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

#include "minirt.h"

bool		check_color_range(char *rgb);
bool			check_color(int	color);
double	get_color(char *str);
void			set_rgb(char *str, t_rgb *rgb);
unsigned int	int_to_hex_color(t_rgb *rgb);

#endif
