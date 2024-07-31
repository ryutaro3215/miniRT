/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:28:27 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/07/26 23:30:03 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/init_data.h"
# include "../includes/utils.h"
# include "../includes/minirt.h"
# include "../includes/color.h"
#include <stdlib.h>

t_ambi_light *get_ambi_light(char **splited_line)
{
	t_ambi_light *ambi_light;
	
	ambi_light = (t_ambi_light *)malloc(sizeof(t_ambi_light));
	ambi_light->ratio = ft_atof(splited_line[1]);
	ambi_light->rgb = (t_rgb *)malloc(sizeof(t_rgb));
	set_rgb(splited_line[2], ambi_light->rgb);
	return (ambi_light);
}

t_camera	*get_camera(char **splited_line)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	camera->view_point = (t_vec3 *)malloc(sizeof(t_vec3));
	camera->nr_vec = (t_vec3 *)malloc(sizeof(t_vec3));
	set_vec3(splited_line[1], camera->view_point);
	set_vec3(splited_line[2], camera->nr_vec);
	camera->view_degree = ft_atoi(splited_line[3]);
	return (camera);
}

t_light	*get_light(char **splited_line)
{
	t_light *light;

	light = (t_light *)malloc(sizeof(t_light));
	light->light_point = (t_vec3 *)malloc(sizeof(t_vec3));
	light->rgb = (t_rgb *)malloc(sizeof(t_rgb));
	set_vec3(splited_line[1], light->light_point);
	set_rgb(splited_line[3], light->rgb);
	light->bright_ratio = ft_atof(splited_line[2]);
	return (light);
}

t_sphere	*get_sphere(char **splited_line)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->center = (t_vec3 *)malloc(sizeof(t_vec3));
	sphere->rgb = (t_rgb *)malloc(sizeof(t_rgb));
	set_vec3(splited_line[1], sphere->center);
	set_rgb(splited_line[3], sphere->rgb);
	sphere->diameter = ft_atof(splited_line[2]);
	return (sphere);
}

t_plane	*get_plane(char **splited_line)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	plane->p_in_the_plane = (t_vec3 *)malloc(sizeof(t_vec3));
	plane->normal_vec = (t_vec3 *)malloc(sizeof(t_vec3));
	plane->rgb = (t_rgb *)malloc(sizeof(t_rgb));
	set_vec3(splited_line[1], plane->p_in_the_plane);
	set_vec3(splited_line[2], plane->normal_vec);
	set_rgb(splited_line[3], plane->rgb);
	return (plane);
}

t_cylinder	*get_cylinder(char **splited_line)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	cylinder->cylinder_center = (t_vec3 *)malloc(sizeof(t_vec3));
	cylinder->axic_vec = (t_vec3 *)malloc(sizeof(t_vec3));
	cylinder->rgb = (t_rgb *)malloc(sizeof(t_rgb));
	cylinder->diameter = ft_atof(splited_line[3]);
	cylinder->height = ft_atof(splited_line[4]);
	set_vec3(splited_line[1], cylinder->cylinder_center);
	set_vec3(splited_line[2], cylinder->axic_vec);
	set_rgb(splited_line[5], cylinder->rgb);
	return (cylinder);
}

bool	get_object(char *line, t_scene *scene)
{
	char	**splited_line;
	char	*attr;

	splited_line = ft_split(line, ' ');
	attr = splited_line[0];
	if (ft_strncmp(attr, "A",ft_strlen(attr)) == 0)
		scene->ambi_light = get_ambi_light(splited_line);
	else if (ft_strncmp(attr, "C", ft_strlen(attr)) == 0)
		scene->camera = get_camera(splited_line);
	else if (ft_strncmp(attr, "L", ft_strlen(attr)) == 0)
		scene->light = get_light(splited_line);
	else if (ft_strncmp(attr, "sp", ft_strlen(attr)) ==0)
		scene->sphere = get_sphere(splited_line);
	else if (ft_strncmp(attr, "pl", ft_strlen(attr)) == 0)
		scene->plane = get_plane(splited_line);
	else if (ft_strncmp(attr, "cy", ft_strlen(attr)) == 0)
		scene->cylinder = get_cylinder(splited_line);
	else
	{
		ft_free_2d_array(splited_line);
		return (false);
	}
	ft_free_2d_array(splited_line);
	return (true);
}

t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	scene->ambi_light = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->sphere = NULL;
	scene->plane = NULL;
	scene->cylinder = NULL;
	return (scene);
}

t_scene	*parse_file(char *file_name, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (get_object(line, scene) == false)
			return (NULL);
		free(line);
		line = get_next_line(fd);
	}
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
