/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:55:08 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/04/29 00:49:18 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*keep_string[OPEN_MAX];
	char		*result_string;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	keep_string[fd] = gnl_read(fd, keep_string[fd]);
	if (!keep_string[fd])
		return (NULL);
	result_string = gnl_get_line(keep_string[fd]);
	keep_string[fd] = gnl_keep_str(keep_string[fd], result_string);
	return (result_string);
}

char	*gnl_read(int fd, char *keep_string)
{
	char	*buffer;
	int		read_bytes;

	read_bytes = 1;
	buffer = (char *)malloc(sizeof(char) * ((long)BUFFER_SIZE + 1));
	if (!buffer)
		return (gnl_free(keep_string));
	while (!gnl_strchr(keep_string, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (gnl_free(keep_string));
		}
		buffer[read_bytes] = '\0';
		keep_string = gnl_strjoin(keep_string, buffer);
		if (!keep_string)
			return (gnl_free(buffer));
	}
	free(buffer);
	return (keep_string);
}

char	*gnl_get_line(char *keep_string)
{
	int		i;
	char	*line_string;

	i = 0;
	if (!keep_string[i])
		return (NULL);
	while (keep_string[i] && keep_string[i] != '\n')
		i++;
	line_string = check_end(keep_string, i);
	if (!line_string)
		return (NULL);
	i = 0;
	while (keep_string[i] && keep_string[i] != '\n')
	{
		line_string[i] = keep_string[i];
		i++;
	}
	if (keep_string[i] == '\n')
	{
		line_string[i] = keep_string[i];
		i++;
	}
	line_string[i] = '\0';
	return (line_string);
}

char	*gnl_keep_str(char *keep_string, char *result_string)
{
	int		i;
	int		j;
	char	*after_n;

	i = 0;
	j = 0;
	if (!result_string)
		return (gnl_free(keep_string));
	while (keep_string[i] && keep_string[i] != '\n')
		i++;
	if (!keep_string[i])
		return (gnl_free(keep_string));
	after_n = malloc(sizeof(char) * (gnl_strlen(keep_string) - i + 1));
	if (!after_n)
	{
		free(result_string);
		return (gnl_free(keep_string));
	}
	i++;
	while (keep_string[i])
		after_n[j++] = keep_string[i++];
	after_n[j] = '\0';
	free(keep_string);
	return (after_n);
}
