# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nammari <nammari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/29 21:34:46 by sdummett          #+#    #+#              #
#    Updated: 2021/12/12 15:33:05 by nammari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ************************************ #
#              VARIABLES               #
# ************************************ #

MAG			= \033[0;35m
WHT			= \033[0;37m
BLK			= \033[0;30m
RED			= \033[0;31m
YEL			= \033[0;33m
GRN			= \033[0;32m
RM			= rm -rf
CC			= clang
CFLAGS		= -Wall -Werror -Wextra -pthread -g3 -fsanitize=address #-v
NAME		= philosophers
SRCS_DIR	= srcs/


ERROR_FILES = $(addprefix error_management/, error_management.c)
PARSE_FILES = $(addprefix parsing/, parse_input.c)
SIMULATION_FILES = $(addprefix simulation/, launch_simulation.c ft_usleep.c\
					 init_time.c init_philosopher_list.c)
UTILS_FILES = $(addprefix utils/, ft_putstr_fd.c free_list.c str_len.c\
 				num_checkers_parsing.c)
SRCS_FILES	=  philosophers.c $(ERROR_FILES) $(PARSE_FILES) $(SIMULATION_FILES)\
 				$(UTILS_FILES)

SRCS 		= $(addprefix ${SRCS_DIR}, ${SRC_FILES})
OBJS_DIR	= objs/
OBJS_FILES	= $(SRCS_FILES:.c=.o)
OBJ			= $(addprefix ${OBJS_DIR}, ${OBJS_FILES})

NAME_BONUS	= philosophers_bonus
SRC_BONUS	= philosophers_bonus.c
OBJ_BONUS	= $(SRC_BONUS:.c=.o)
INC			= -Iinclude
includes	= $(wildcard include/*.h)

OBJS_SUB_DIRS = $(addprefix objs/, error_management parsing simulation utils) 

# ************************************ #
#                RULES                 #
# ************************************ #

all: $(NAME)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)
	mkdir $(OBJS_SUB_DIRS)

$(NAME): $(OBJS_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "$(WHT)[$(GRN)$(NAME) COMPILED$(WHT)]\n"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(include)
	$(CC) $(INC) -c $(CFLAGS) -o $@ $<

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_BONUS)
	@printf "$(WHT)[$(YEL)$(NAME) OBJS REMOVED$(WHT)]\n"

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJS_DIR)
	@printf "$(WHT)[$(YEL)$(NAME) BINARIES REMOVED$(WHT)]\n"

re: fclean all
