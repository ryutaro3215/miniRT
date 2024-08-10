/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:15:21 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/08/10 16:44:40 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/includes/libft.h"
# include "minirt.h"

bool	is_num(char *str);
bool	is_point_num(char *str);
void	free_ambi_light(t_ambi_light *ambi_light);
void	free_camera(t_camera *camera);
void	free_light(t_light *light);
void	free_sphere(t_object *sphere);
void	free_plane(t_object *plane);
void	free_cylinder(t_object *cylinder);
void	free_scene(t_scene *scene);
void	print_scene(t_scene *scene);
size_t	ft_2d_array_len(char **array);
void	ft_free_2d_array(char **array);

#endif
