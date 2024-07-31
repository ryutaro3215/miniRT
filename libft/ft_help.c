/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:34:48 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/01/22 16:42:29 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	ft_count_int(int num)
{
	int		digit_count;
	long	long_num;

	digit_count = 0;
	long_num = num;
	if (num == 0)
		return (1);
	if (long_num < 0)
	{
		digit_count++;
		long_num *= -1;
	}
	while (long_num > 0)
	{
		digit_count++;
		long_num = long_num / 10;
	}
	return (digit_count);
}

int	ft_count_unsigned_int(unsigned int num)
{
	int		digit_count;

	digit_count = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		digit_count++;
		num = num / 10;
	}
	return (digit_count);
}

int	ft_count_hex(unsigned int num)
{
	int		hex_count;

	hex_count = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		hex_count++;
		num = num / 16;
	}
	return (hex_count);
}
