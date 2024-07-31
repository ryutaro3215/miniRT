/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:16:35 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/07/24 19:06:05 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

#include "minirt.h"

bool			check_color(int	color);
unsigned int	get_color(char *str);
void			set_rgb(char *str, t_rgb *rgb);

#endif
