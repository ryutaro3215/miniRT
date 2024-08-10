/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:18:31 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/08/10 11:22:46 by yoshidakazu      ###   ########.fr       */
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




t_rt			*make_data_structure();
t_scene			*parse_file(char *file_name, t_scene *scene);
t_scene			*init_scene();
bool			get_object(char *line, t_scene *scene);
void get_ambi_light(char **splited_line,t_scene *scene);
void 	get_camera(char **splited_line,t_scene *scene);
void 	get_light(char **splited_line,t_scene *scene);
void 	get_sphere(char **splited_line,t_scene *scene);
void 	get_plane(char **splited_line,t_scene *scene);
void 	get_cylinder(char **splited_line,t_scene *scene);

#endif
