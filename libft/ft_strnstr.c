/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:52:55 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/01/22 16:40:31 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*h;
	char	*n;
	size_t	i;

	while (!(*needle))
		return ((char *)haystack);
	while (len > 0 && *haystack != '\0')
	{
		h = (char *)haystack;
		n = (char *)needle;
		i = len;
		while (*n != '\0' && (*h == *n) && i > 0)
		{
			h++;
			n++;
			i--;
		}
		if (!(*n))
			return ((char *)haystack);
		len--;
		haystack++;
	}
	return (NULL);
}
