/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:55:55 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/04/29 00:48:45 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line.h"

size_t	gnl_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*gnl_strchr(char *str, int c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	if (c == '\0')
		return ((char *)&str[gnl_strlen(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

char	*gnl_strjoin(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*result;

	i = -1;
	j = 0;
	if (!str1)
	{
		str1 = (char *)malloc(1 * sizeof(char));
		if (!str1)
			return (NULL);
		str1[0] = '\0';
	}
	if (!str1 || !str2)
		return (NULL);
	result = malloc(sizeof(char) * (gnl_strlen(str1) + gnl_strlen(str2) + 1));
	if (!result)
		return (NULL);
	while (str1[++i] != '\0')
		result[i] = str1[i];
	while (str2[j] != '\0')
		result[i++] = str2[j++];
	result[i] = '\0';
	free(str1);
	return (result);
}

char	*gnl_free(char *str)
{
	free(str);
	return (NULL);
}

char	*check_end(char *keep_string, int i)
{
	char	*line_string;

	if (keep_string[i] == '\0')
		line_string = (char *)malloc(sizeof(char) * (i + 1));
	else
		line_string = (char *)malloc(sizeof(char) * (i + 2));
	if (!line_string)
		return (NULL);
	return (line_string);
}
