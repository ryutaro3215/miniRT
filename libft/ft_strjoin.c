/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:19:52 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/01/22 16:40:10 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concat_str;
	int		j;
	int		i;
	int		s1_len;
	int		s2_len;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	concat_str = (char *)malloc(s1_len + s2_len + 1);
	if (concat_str == NULL)
		return (NULL);
	while (s1[i] != '\0')
		concat_str[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		concat_str[j++] = s2[i++];
	concat_str[j] = '\0';
	return (concat_str);
}
