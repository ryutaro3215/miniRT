/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:33:06 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/01/22 16:38:36 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cs;
	unsigned char	word;

	cs = (unsigned char *)s;
	word = (unsigned char)c;
	while (n > 0)
	{
		if (*cs == word)
			return (cs);
		n--;
		cs++;
	}
	return (NULL);
}
