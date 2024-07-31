/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:04:47 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/04/18 10:53:33 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	judge_identifer(va_list *argument, char word);

int	ft_printf(const char *str, ...)
{
	va_list	argument;
	int		i;
	int		print_len;

	va_start(argument, str);
	i = 0;
	print_len = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '%')
			print_len += ft_print_char(str[i]);
		else
		{
			print_len += judge_identifer(&argument, str[i + 1]);
			i++;
		}
		i++;
	}
	va_end(argument);
	return (print_len);
}

int	judge_identifer(va_list *argument, char word)
{
	int	print_len;

	print_len = 0;
	if (word == 'c')
		print_len = ft_print_char(va_arg(*argument, int));
	else if (word == 's')
		print_len = ft_print_string(va_arg(*argument, char *));
	else if (word == 'p')
		print_len = ft_print_pointer(va_arg(*argument, unsigned long long));
	else if (word == 'd' || word == 'i')
		print_len = ft_print_signed_int(va_arg(*argument, int));
	else if (word == 'u')
		print_len = ft_print_unsigned_int(va_arg(*argument, unsigned int));
	else if (word == 'x')
		print_len = ft_print_low_hex(va_arg(*argument, unsigned int));
	else if (word == 'X')
		print_len = ft_print_upp_hex(va_arg(*argument, unsigned int));
	else if (word == '%')
		print_len = ft_print_char('%');
	else
		print_len = 0;
	return (print_len);
}

// int	main(void)
// {
// 	char *str = NULL;
// 	char *string;
// 	string = "";
// 	printf("return value : %d\n",
// 	printf("original\nchar : %c\nstring : %s\npointer : %p\ninteger : %i\n
// 	integer : %d\nunint : %u\nlowhex : %x\nupphex : %X\n",
// 		'\t', string, str, INT_MIN, INT_MAX, UINT_MAX, 1234, 1234));
// 	ft_printf("return value : %d\n",
// 	ft_printf("myprintf\nchar : %c\nstring : %s\npointer : %p\ninteger : %i\n
// 	integer : %d\nunint : %u\nlowhex : %x\nupphex : %X\n",
// 		'\t', string, str, INT_MIN, INT_MAX, UINT_MAX, 1234, 1234));
// }
