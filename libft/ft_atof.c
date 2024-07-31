/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:43:32 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/07/24 11:09:56 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/* double	check_float_range(double result) */
/* { */
/* 	if (result > FLT_MAX) */
/* 		return (FLT_MAX); */
/* 	if (result < -FLT_MAX) */
/* 		return (-FLT_MAX); */
/* 	return (result); */
/* } */

double	culc_double(char c, float *factor, double result, int point_flag)
{
	if (point_flag == 0)
		result = result * 10 + (c - '0');
	else
	{
		*factor *= 0.1f;
		result += *factor * (c - '0');
	}
	return (result);
}

double	make_double(char *str)
{
	int		point_flag;
	double	result;
	float	factor;

	point_flag = 0;
	result = 0.0;
	factor = 1.0f;
	while (*str)
	{
		if (*str == '.')
			point_flag = 1;
		else if (*str <= '9' && *str >= '0')
			result = culc_double(*str, &factor, result, point_flag);
		else
			break ;
		str++;
	}
	return (result);
}

float	ft_atof(char *str)
{
	double	result;
	float	sign;

	sign = 1.0f;
	result = 0.0;
	if (*str == '-')
	{
		sign = -1.0f;
		str++;
	}
	result = make_double(str);
	result *= sign;
	return ((float)result);
}
