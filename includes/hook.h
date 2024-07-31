/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:52:58 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/07/26 22:54:29 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_H
# define HOOK_H

# include <unistd.h>
# include "../minilibx-linux/mlx.h"
# include "../includes/minirt.h"

# define ESC 65307

int		close_win(t_rt *rt);
int		key_press(int keynum, t_rt *rt);
void	hook_event(t_rt *rt);

#endif
