/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:18:31 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/10/09 17:55:46 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_DATA_H
# define INIT_DATA_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/includes/libft.h"
# include "../includes/minirt.h"

char		**get_splited_line(char *line);
char		*trim_newline(char *line);
int			count_2d_array(char **array);
t_rt		*make_data_structure(void);
t_scene		*parse_file(char *file_name, t_scene *scene);
t_scene		*init_scene(void);
t_object	*init_object(void);
bool		get_env(char *line, t_scene *scene);
bool		get_object(char **splited_line, t_scene *scene);
t_object	*get_last_object(t_object *object);
bool		check_ambi_param(char **splited_line);
bool		get_ambi_light(char **splited_line, t_scene *scene);
bool		get_camera(char **splited_line, t_scene *scene);
bool		get_light(char **splited_line, t_scene *scene);
bool		get_sphere(char **splited_line, t_scene *scene);
bool		get_plane(char **splited_line, t_scene *scene);
bool		get_cylinder(char **splited_line, t_scene *scene);

#endif
