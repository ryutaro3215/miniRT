/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:54:08 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/01/22 16:37:45 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static long	make_int(const char *str, long flag);
static long	check_number(long number, long flag, long next_num);

int	ft_atoi(const char *str)
{
	long	flag;

	flag = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			flag = -1;
		str++;
	}
	return (make_int(str, flag));
}

static long	make_int(const char *str, long flag)
{
	long	number;
	int		i;

	number = 0;
	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
	{
		number = str[i] - '0';
		i++;
		while (str[i] && str[i] >= '0' && str[i] <= '9')
		{
			number = number * 10;
			if (check_number(number, flag, str[i] - '0') != 1)
				return (check_number(number, flag, str[i] - '0'));
			number = number + str[i] - '0';
			i++;
		}
		return ((int)(number * flag));
	}
	return (0);
}

static long	check_number(long number, long flag, long next_num)
{
	if ((number * flag) > (LONG_MAX / 10))
		return ((int)LONG_MAX);
	if ((number * flag) == (LONG_MAX / 10) && next_num > (LONG_MAX % 10))
		return ((int)LONG_MAX);
	if ((number * flag) < (LONG_MIN / 10))
		return ((int)LONG_MIN);
	if ((number * flag) == (LONG_MIN / 10) && (next_num * -1) < (LONG_MIN % 10))
		return ((int)LONG_MIN);
	return (1);
}
