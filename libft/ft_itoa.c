/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:36:06 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/01/22 16:38:25 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static void	insert_string(long ln, char *string_num, int digit);
static long	digit_count(long n);

char	*ft_itoa(int n)
{
	int		digit;
	long	ln;
	char	*string_num;

	ln = n;
	digit = digit_count(ln);
	string_num = (char *)malloc(digit + 1);
	if (string_num == NULL)
		return (NULL);
	insert_string(ln, string_num, digit);
	return (string_num);
}

static void	insert_string(long ln, char *string_num, int digit)
{
	int	i;

	i = digit - 1;
	if (ln != 0)
	{
		if (ln < 0)
		{
			ln = -ln;
			string_num[0] = '-';
		}
		while (i >= 0 && ln > 0)
		{
			string_num[i] = (ln % 10) + '0';
			i--;
			ln = ln / 10;
		}
		string_num[digit] = '\0';
	}
	else
	{
		string_num[0] = '0';
		string_num[1] = '\0';
	}
	return ;
}

static long	digit_count(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}
