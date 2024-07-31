# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 18:37:00 by rmatsuba          #+#    #+#              #
#    Updated: 2024/07/24 10:29:43 by rmatsuba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atof.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_striteri.c \
ft_tolower.c ft_toupper.c ft_substr.c \
ft_help.c ft_print_num.c ft_print_pointer.c ft_print_word.c ft_printf.c \
get_next_line.c get_next_line_utils.c \
ft_lstadd_front.c ft_lstadd_back.c \
ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c \
ft_lstnew.c ft_lstsize.c

OBJS = ${SRCS:.c=.o}
# BONUS_OBJS = ${BONUS_SRCS:.c=.o}
CFLAGS = -Wall -Wextra -Werror
CC = cc
NAME = libft.a
INCLUDE = -I include

# ifeq ($(MAKECMDGOALS), bonus)
# 	SRCS += ${BONUS_SRCS}
# 	OBJS += ${BONUS_OBJS}
# endif

all : ${NAME}

${NAME} : ${OBJS}
	@ar -rcs ${NAME} ${OBJS}
	@echo "libft.a created!"

%.o: %.c
	@${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@
	@echo "Compiled "$<" successfully!"
clean :
	@rm -f ${OBJS} ${BONUS_OBJS}
	@echo "Object files removed!"

fclean : clean
	@rm -f ${NAME}
	@echo "libft.a removed!"

re : fclean all

bonus: all

.PHONY:			all clean fclean re bonus
