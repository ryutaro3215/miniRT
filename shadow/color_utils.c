/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:00:10 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/10/10 12:16:51 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shadow.h"
#include "../includes/ray_cross.h"

t_rgb   color_init2(double r, double g, double b)
{
    t_rgb   color;

    color.r = r;
    color.g = g;
    color.b = b;
    return (check_color_is_valid(color));
    // return color;
}

t_rgb color_mul(t_rgb a, t_rgb b)
{
    a.r *= b.r;
    a.g *= b.g;
    a.b *= b.b;
    return check_color_is_valid(a);
    // return a;
}

t_rgb color_mul_scalar(t_rgb a, double b)
{
    a.r *= b;
    a.g *= b;
    a.b *= b;
   
    return check_color_is_valid(a);
    // return a;
}

t_rgb color_add(t_rgb a, t_rgb b)
{
    a.r += b.r;
    a.g += b.g;
    a.b += b.b;
    return check_color_is_valid(a);
    // return a;
}
uint32_t color_ans(int r,int g , int b)
{
    	uint32_t	color;
    color = (r << 16) | (g  << 8) | b ;
	return (color);
}