# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nammari <nammari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 13:08:00 by nammari           #+#    #+#              #
#    Updated: 2021/12/16 14:33:30 by nammari          ###   ########.fr        #
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
		rm $(NAME)

re:	fclean all