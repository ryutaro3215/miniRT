/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:28:27 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/09 17:50:44 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/init_data.h"
#include "../includes/utils.h"
#include "../includes/minirt.h"
#include "../includes/color.h"
#include <stddef.h>
#include <stdlib.h>

char	**get_splited_line(char *line)
{
	char	**splited_line;

	if (line == NULL || ft_strlen(line) == 0)
		return (NULL);
	splited_line = ft_split(line, ' ');
	return (splited_line);
}

bool	get_env(char *line, t_scene *scene)
{
	char	**splited_line;
	char	*attr;
	bool	flag;

	splited_line = get_splited_line(line);
	if (splited_line == NULL)
		return (false);
	attr = splited_line[0];
	flag = true;
	if (ft_strncmp(attr, "A", ft_strlen(attr)) == 0)
		flag = get_ambi_light(splited_line, scene);
	else if (ft_strncmp(attr, "C", ft_strlen(attr)) == 0)
		flag = get_camera(splited_line, scene);
	else if (ft_strncmp(attr, "L", ft_strlen(attr)) == 0)
		flag = get_light(splited_line, scene);
	else
		flag = get_object(splited_line, scene);
	if (flag == false)
	{
		ft_free_2d_array(splited_line);
		return (false);
	}
	ft_free_2d_array(splited_line);
	return (true);
}

char	*trim_newline(char *line)
{
	char	*new_line;

	if (line == NULL)
		return (NULL);
	if (line[0] == '\n' && ft_strlen(line) == 1)
		return (line);
	if (ft_strchr(line, '\n') == NULL)
		return (line);
	new_line = ft_strndup(line, ft_strlen(line) - 1);
	if (new_line == NULL)
		return (NULL);
	free(line);
	return (new_line);
}

t_scene	*parse_file(char *file_name, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while (true)
	{
		line = trim_newline(get_next_line(fd));
		if (line == NULL)
			break ;
		else if (ft_strncmp(line, "\n", 1) == 0 && ft_strlen(line) == 1)
			continue ;
		else if (get_env(line, scene) == false)
		{
			free(line);
			return (NULL);
		}
		free(line);
	}
	if (scene->camera == NULL && scene->object == NULL
		&& scene->ambi_light == NULL && scene->light == NULL)
		return (NULL);
	return (scene);
}

t_rt	*make_data_structure(void)
{
	t_rt	*rt;

	rt = (t_rt *)malloc(sizeof(t_rt));
	rt->width = 1000;
	rt->height = 1000;
	rt->mlx = mlx_init();
	rt->mlx_win = mlx_new_window(rt->mlx, rt->width, rt->height, "miniRT");
	rt->img = mlx_new_image(rt->mlx, rt->width, rt->height);
	rt->addr = mlx_get_data_addr(rt->img, &rt->bpp, &rt->line_len, &rt->endian);
	rt->scene = NULL;
	return (rt);
}
