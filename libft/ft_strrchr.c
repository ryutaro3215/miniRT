/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:15:10 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/01/22 16:40:34 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	w;
	int				i;
	const char		*rev_ad;

	i = ft_strlen((char *)s);
	w = (unsigned char)c;
	rev_ad = s + i;
	while (i >= 0)
	{
		if (*rev_ad == w)
			return ((char *)rev_ad);
		rev_ad--;
		i--;
	}
	return (NULL);
}
