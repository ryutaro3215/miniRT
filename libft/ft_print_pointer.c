/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:44:37 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/03/04 17:53:10 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	ft_count_pointer(unsigned long long address)
{
	int		address_count;

	address_count = 0;
	if (address == 0)
		return (1);
	while (address > 0)
	{
		address_count++;
		address = address / 16;
	}
	return (address_count);
}

int	ft_print_address(unsigned long long address)
{
	if (address >= 16)
		ft_print_address(address / 16);
	if (address % 16 >= 10)
		ft_print_char((address % 16 - 10) + 'a');
	else
		ft_print_char((address % 16) + '0');
	return (ft_count_hex(address));
}

int	ft_print_pointer(unsigned long long address)
{
	int	address_len;

	address_len = ft_count_pointer(address);
	write(1, "0x", 2);
	address_len += 2;
	if (address >= 16)
		ft_print_address(address / 16);
	if (address % 16 >= 10)
		ft_print_char((address % 16 - 10) + 'a');
	else
		ft_print_char((address % 16) + '0');
	return (address_len);
}
