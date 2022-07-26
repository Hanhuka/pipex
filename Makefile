# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 16:26:20 by ralves-g          #+#    #+#              #
#    Updated: 2022/07/26 16:29:36 by ralves-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
# -fsanitize=address -g
RM			=	rm -f

NAME		=	pipex

INCLUDE		=	-I ./
SRCS_		=	\
				pipex.c \
				parsing.c \
				child_work.c \
				errors_and_frees.c \
				split.c \
				utils.c \
				get_next_line.c \
				get_next_line_utils.c

SRCS		=	$(addprefix $(_SRC), $(SRCS_))

_OBJ		=	./obj/
_SRC		= 	./src/
OBJS		=	$(patsubst $(_SRC)%.c, $(_OBJ)%.o, $(SRCS))

all:		$(NAME)

$(_OBJ)%.o: $(_SRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDE)

#bonus:		$(SRCS_B) $(OBJS_B)
#			$(CC) $(CFLAGS) $(SRCS_B) -o $(NAME_B)
#			$(CC) $(CFLAGS) $(SRCS_B) -c

$(_OBJ):
	mkdir $@

clean:
	$(RM) -r $(_OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean flean re
