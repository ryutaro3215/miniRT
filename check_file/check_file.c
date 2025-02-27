/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:34:57 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/09 17:06:57 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/check_file.h"
#include "../includes/minirt.h"

bool	check_extension(char *file_name, char *extension)
{
	char	*file_extension;
	int		word_len;

	word_len = ft_strlen(file_name);
	file_extension = &file_name[word_len - 3];
	if (!file_extension || ft_strlen(file_extension) != 3)
		return (false);
	if (ft_strncmp(file_extension, extension, 3) == 0)
		return (true);
	return (false);
}

bool	check_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("could not open file");
		return (false);
	}
	close(fd);
	if (!check_extension(file_name, ".rt"))
		return (false);
	return (true);
}
