/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 13:57:55 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/01/22 16:39:54 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	w;

	w = (unsigned char)c;
	while (*s != '\0')
	{
		if (*s == w)
			return ((char *)s);
		s++;
	}
	if (w == '\0')
		return ((char *)s);
	return (NULL);
}
