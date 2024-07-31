/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:57:18 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/01/22 16:39:04 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	ft_print_signed_int(int num)
{
	long	long_num;
	char	character;

	long_num = num;
	if (long_num < 0)
	{
		write(1, "-", 1);
		long_num = -long_num;
	}
	if (long_num >= 10)
		ft_print_signed_int(long_num / 10);
	character = (long_num % 10) + '0';
	write(1, &character, 1);
	return (ft_count_int(num));
}

int	ft_print_unsigned_int(unsigned int un_num)
{
	char	character;

	if (un_num >= 10)
		ft_print_unsigned_int(un_num / 10);
	character = (un_num % 10) + '0';
	write(1, &character, 1);
	return (ft_count_unsigned_int(un_num));
}

int	ft_print_low_hex(unsigned int num)
{
	if (num >= 16)
		ft_print_low_hex(num / 16);
	if (num % 16 >= 10)
		ft_print_char((num % 16 - 10) + 'a');
	else
		ft_print_char((num % 16) + '0');
	return (ft_count_hex(num));
}

int	ft_print_upp_hex(unsigned int num)
{
	if (num >= 16)
		ft_print_upp_hex(num / 16);
	if (num % 16 >= 10)
		ft_print_char((num % 16 - 10) + 'A');
	else
		ft_print_char((num % 16) + '0');
	return (ft_count_hex(num));
}
