# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: noufel <noufel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 13:08:00 by nammari           #+#    #+#              #
#    Updated: 2022/01/08 12:12:24 by noufel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES = ft_atoul.c ft_putstr_fd.c ft_ultoa.c num_checkers.c \
str_len.c ft_strcmp.c

CC		= gcc -c

AR		= ar

ARFLAGS	= rc

CFLAGS	= -Wextra -Wall -Werror

INCLUDES = includes/utils_lib.h

NAME	= my_library.a

SRCS 	= $(addprefix srcs/, $(SRCS_FILES))

OBJS = $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
		$(AR) $(ARFLAGS) $(NAME) $(OBJS)
		ranlib $(NAME)

%.o:	%.c $(INCLUDES)
		$(CC) -Iincludes -o $@ $< $(CFLAGS)

clean:
		rm -rf $(OBJS)

fclean:	clean
		rm -rf $(NAME)

re:	fclean all