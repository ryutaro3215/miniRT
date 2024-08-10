/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:28:27 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/08/10 20:07:56 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/init_data.h"
# include "../includes/utils.h"
# include "../includes/minirt.h"
# include "../includes/color.h"
#include <stddef.h>
#include <stdlib.h>

bool	check_ambi_param(char **splited_line)
{
	float	ratio;

	if (ft_2d_array_len(splited_line) != 3)
		return (false);
	if (is_point_num(splited_line[1]) == false)
		return (false);
	ratio = ft_atof(splited_line[1]);
	if (ratio < 0.0f || ratio > 1.0f)
		return (false);
	if (check_color_range(splited_line[2]) == false)
		return (false);
	return (true);
}

bool	get_ambi_light(char **splited_line, t_scene *scene)
{
	t_ambi_light *ambi_light;

	if (check_ambi_param(splited_line) == false)
		return (false);
	ambi_light = (t_ambi_light *)malloc(sizeof(t_ambi_light));
	ambi_light->ratio = ft_atof(splited_line[1]);
	ambi_light->rgb = (t_rgb *)malloc(sizeof(t_rgb));
	set_rgb(splited_line[2], ambi_light->rgb);
	scene->ambi_light = ambi_light;
	return (true);
}

bool	check_camera_param(char **splited_line)
{
	bool	flag;

	flag = true;
	if (ft_2d_array_len(splited_line) != 4)
		return (false);
	if (is_vec3(splited_line[1]) == false)
		flag = false;
	if (is_vec3(splited_line[2]) == false || is_normal_vec3(splited_line[2]) == false)
		flag = false;
	if (is_num(splited_line[3]) == false || ft_atoi(splited_line[3]) <= 0
			|| ft_atoi(splited_line[3]) >= 180)
		flag = false;
	return (flag);
}

bool	get_camera(char **splited_line, t_scene *scene)
{
	t_camera	*camera;

	if (check_camera_param(splited_line) == false)
		return (false);
	camera = (t_camera *)malloc(sizeof(t_camera));
	camera->view_point = (t_vec3 *)malloc(sizeof(t_vec3));
	camera->nr_vec = (t_vec3 *)malloc(sizeof(t_vec3));
	set_vec3(splited_line[1], camera->view_point);
	set_vec3(splited_line[2], camera->nr_vec);
	camera->view_degree = ft_atoi(splited_line[3]);
	scene->camera = camera;
	return (true);
}

bool	check_light_param(char **splited_line)
{
	bool	flag;

	flag = true;
	if (ft_2d_array_len(splited_line) != 4)
		return (false);
	if (is_vec3(splited_line[1]) == false)
		flag = false;
	if (is_point_num(splited_line[2]) == false || ft_atof(splited_line[2]) < 0.0f
			|| ft_atof(splited_line[2]) > 1.0f)
		flag = false;
	if (check_color_range(splited_line[3]) == false)
		flag = false;
	return (flag);
}

bool	get_light(char **splited_line, t_scene *scene)
{
	t_light *light;

	if (check_light_param(splited_line) == false)
		return (false);
	light = (t_light *)malloc(sizeof(t_light));
	light->light_point = (t_vec3 *)malloc(sizeof(t_vec3));
	light->rgb = (t_rgb *)malloc(sizeof(t_rgb));
	set_vec3(splited_line[1], light->light_point);
	set_rgb(splited_line[3], light->rgb);
	light->bright_ratio = ft_atof(splited_line[2]);
	scene->light = light;
	return (true);
}

t_object	*init_object()
{
	t_object	*object;

	object = (t_object *)malloc(sizeof(t_object));
	object->type = 0;
	object->center = NULL;
	object->p_in_the_plane = NULL;
	object->normal_vec = NULL;
	object->axic_vec = NULL;
	object->rgb = NULL;
	object->diameter = 0;
	object->height = 0;
	object->next = NULL;
	return (object);
}

bool	check_sphere_param(char **splited_line)
{
	bool	flag;

	flag = true;
	if (ft_2d_array_len(splited_line) != 4)
		return (false);
	if (is_vec3(splited_line[1]) == false)
		flag = false;
	if (is_point_num(splited_line[2]) == false || ft_atof(splited_line[2]) <= 0)
	{
		flag = false;
		printf("Invalid diameter\n");
	}
	if (check_color_range(splited_line[3]) == false)
	{
		flag = false;
		printf("Invalid color\n");
	}
	return (flag);
}

bool	get_sphere(char **splited_line, t_scene *scene)
{
	t_object	*sphere;

	if (check_sphere_param(splited_line) == false)
		return (false);
	sphere = init_object();
    sphere->type = SPHERE;
	sphere->center = (t_vec3 *)malloc(sizeof(t_vec3));
	sphere->rgb = (t_rgb *)malloc(sizeof(t_rgb));
	set_vec3(splited_line[1], sphere->center);
	set_rgb(splited_line[3], sphere->rgb);
	sphere->diameter = ft_atof(splited_line[2]);
	sphere->next = scene->object;
	scene->object = sphere;
	return (true);
}

bool	check_plane_param(char **splited_line)
{
	bool	flag;

	flag = true;
	if (ft_2d_array_len(splited_line) != 4)
		return (false);
	if (is_vec3(splited_line[1]) == false)
		flag = false;
	if (is_normal_vec3(splited_line[2]) == false)
		flag = false;
	if (check_color_range(splited_line[3]) == false)
		flag = false;
	return (flag);
}

bool	get_plane(char **splited_line, t_scene *scene)
{
	t_object	*plane;

	if (check_plane_param(splited_line) == false)
		return (false);
	plane = init_object();
    plane->type = PLANE;
	plane->p_in_the_plane = (t_vec3 *)malloc(sizeof(t_vec3));
	plane->normal_vec = (t_vec3 *)malloc(sizeof(t_vec3));
	plane->rgb = (t_rgb *)malloc(sizeof(t_rgb));
	set_vec3(splited_line[1], plane->p_in_the_plane);
	set_vec3(splited_line[2], plane->normal_vec);
	set_rgb(splited_line[3], plane->rgb);
	plane->next = scene->object;
	scene->object = plane;
	return (true);
}

bool	check_cylinder_param(char **splited_line)
{
	bool	flag;

	flag = true;
	if (ft_2d_array_len(splited_line) != 6)
		return (false);
	if (is_vec3(splited_line[1]) == false)
		flag = false;
	if (is_normal_vec3(splited_line[2]) == false)
		flag = false;
	if ((is_point_num(splited_line[3]) == false || ft_atof(splited_line[3]) <= 0)
			|| (is_point_num(splited_line[4]) == false || ft_atof(splited_line[4]) <= 0))
		flag = false;
	if (check_color_range(splited_line[5]) == false)
		flag = false;
	return (flag);
}

bool	get_cylinder(char **splited_line, t_scene *scene)
{
	// t_cylinder	*cylinder;
    t_object    *cylinder;
    
	if (check_cylinder_param(splited_line) == false)
		return (false);
	cylinder = init_object();
    cylinder->type = CYLINDER;
	cylinder->center = (t_vec3 *)malloc(sizeof(t_vec3));
	cylinder->axic_vec = (t_vec3 *)malloc(sizeof(t_vec3));
	cylinder->rgb = (t_rgb *)malloc(sizeof(t_rgb));
	cylinder->diameter = ft_atof(splited_line[3]);
	cylinder->height = ft_atof(splited_line[4]);
	set_vec3(splited_line[1], cylinder->center);
	set_vec3(splited_line[2], cylinder->axic_vec);
	set_rgb(splited_line[5], cylinder->rgb);
	cylinder->next = scene->object;
	scene->object = cylinder;
	return (true);
}

bool	get_object(char **splited_line, t_scene *scene)
{
	char	*attr;
	bool	flag;
	/* t_object	*last_object; */

	flag = true;
	attr = splited_line[0];
	if (ft_strncmp(attr, "sp", ft_strlen(attr)) == 0)
		flag = get_sphere(splited_line, scene);
	else if (ft_strncmp(attr, "pl", ft_strlen(attr)) == 0)
		flag = get_plane(splited_line, scene);
	else if (ft_strncmp(attr, "cy", ft_strlen(attr)) == 0)
		flag = get_cylinder(splited_line, scene);
	else
		flag = false;
	return (flag);
}

bool	get_env(char *line, t_scene *scene)
{
	char	**splited_line;
	char	*attr;
	bool	flag;

	splited_line = ft_split(line, ' ');
	attr = splited_line[0];
	flag = true;
	if (ft_strncmp(attr, "A",ft_strlen(attr)) == 0)
		flag = get_ambi_light(splited_line,scene);
	else if (ft_strncmp(attr, "C", ft_strlen(attr)) == 0)
		flag = get_camera(splited_line,scene);
	else if (ft_strncmp(attr, "L", ft_strlen(attr)) == 0)
		flag = get_light(splited_line,scene);
	else
		flag = get_object(splited_line,scene);
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
	int	i;

	i = 0;
	if (line == NULL || ft_strlen(line) == 0)
		return (NULL);
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
	return (line);
}

t_scene	*parse_file(char *file_name, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = trim_newline(get_next_line(fd));
	while (line != NULL)
	{
		if (get_env(line, scene) == false)
			return (NULL);
		free(line);
		line = trim_newline(get_next_line(fd));
	}
	return (scene);
}

t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	scene->ambi_light = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->object = NULL;
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
