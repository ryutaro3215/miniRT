/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:18:31 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/09/16 20:48:06 by yoshidakazu      ###   ########.fr       */
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



int	count_2d_array(char **array);
t_rt	*make_data_structure();
t_scene	*parse_file(char *file_name, t_scene *scene);
t_scene	*init_scene();
t_object	*init_object();
bool	get_env(char *line, t_scene *scene);
bool	get_object(char **splited_line, t_scene *scene);
t_object	*get_last_object(t_object *object);
bool	check_ambi_param(char **splited_line);
bool	get_ambi_light(char **splited_line,t_scene *scene);
bool	get_camera(char **splited_line,t_scene *scene);
bool	get_light(char **splited_line,t_scene *scene);
bool	get_sphere(char **splited_line,t_scene *scene);
bool	get_plane(char **splited_line,t_scene *scene);
bool	get_cylinder(char **splited_line,t_scene *scene);
#endif
