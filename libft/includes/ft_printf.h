/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:01:39 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/04/18 10:53:47 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>

int	ft_printf(const char *str, ...);
int	judge_identifer(va_list *argument, char word);
int	ft_print_char(int chr);
int	ft_print_string(char *str);
int	ft_print_signed_int(int num);
int	ft_print_unsigned_int(unsigned int un_num);
int	ft_print_low_hex(unsigned int num);
int	ft_print_upp_hex(unsigned int num);
int	ft_strlen(char *str);
int	ft_count_int(int num);
int	ft_count_unsigned_int(unsigned int num);
int	ft_count_hex(unsigned int num);
int	ft_print_pointer(unsigned long long address);
int	ft_count_pointer(unsigned long long address);
int	ft_print_address(unsigned long long address);

#endif
