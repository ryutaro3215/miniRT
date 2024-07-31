/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:55:35 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/04/29 00:49:56 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

char	*get_next_line(int fd);
char	*gnl_read(int fd, char *keep_string);
char	*gnl_get_line(char *keep_string);
char	*gnl_keep_str(char *keep_string, char *result_string);
char	*gnl_free(char *str);
char	*gnl_strchr(char *s, int c);
size_t	gnl_strlen(char *s);
char	*gnl_strjoin(char *s1, char *s2);
char	*check_end(char *keep_string, int i);

#endif
