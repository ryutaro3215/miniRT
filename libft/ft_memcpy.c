/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:26:50 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/01/22 16:38:47 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*destnation;
	unsigned char	*source;

	i = 0;
	destnation = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (destnation == NULL && source == NULL)
		return (dst);
	while (i < n)
	{
		destnation[i] = source[i];
		i++;
	}
	return (dst);
}
