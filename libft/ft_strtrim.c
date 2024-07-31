/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:12:18 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/01/22 16:40:37 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	is_set(char c, char const *set);
static int	count_size(char const *s1, char const *s2);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimed_str;
	int		j;
	int		mem_size;

	j = 0;
	if (!s1)
		return (NULL);
	mem_size = count_size(s1, set);
	trimed_str = (char *)malloc(mem_size + 1);
	if (!(trimed_str))
		return (NULL);
	while (*s1 != '\0')
	{
		if (!is_set(*s1, set))
		{
			while (mem_size--)
				trimed_str[j++] = *s1++;
			trimed_str[j] = '\0';
			return (trimed_str);
		}
		s1++;
	}
	trimed_str[0] = '\0';
	return (trimed_str);
}

static int	count_size(char const *s1, char const *s2)
{
	int	head;
	int	tail;
	int	i;
	int	s1_len;

	head = 0;
	tail = 0;
	i = 0;
	s1_len = ft_strlen(s1);
	while (is_set(s1[i], s2))
	{
		head++;
		i++;
	}
	if (head == s1_len)
		return (0);
	i = s1_len - 1;
	while (is_set(s1[i], s2))
	{
		tail++;
		i--;
	}
	return (s1_len - head - tail);
}

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
