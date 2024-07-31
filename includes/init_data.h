/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:18:31 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/07/26 22:57:56 by rmatsuba         ###   ########.fr       */
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
t_ambi_light	*get_ambi_light(char **splited_line);
t_camera		*get_camera(char **splited_line);
t_light			*get_light(char **splited_line);
t_sphere		*get_sphere(char **splited_line);
t_plane			*get_plane(char **splited_line);
t_cylinder		*get_cylinder(char **splited_line);

#endif
