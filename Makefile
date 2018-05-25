# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/13 13:47:25 by gvynogra          #+#    #+#              #
#    Updated: 2018/05/25 18:01:47 by gvynogra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = minishell.c parser.c builtin.c execution.c environement.c built_functions.c list_manage.c help_funcs.c
LIB = libft/libft.a
OBJ = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror
HDRS = minishell.h libft/includes/ft_printf.h libft/includes/get_next_line.h libft/includes/libft.h
all:	$(NAME)

$(NAME): $(OBJ) $(LIB) $(HDRS)
	gcc -o $(NAME) $(FLAGS) $(OBJ) -L. $(LIB)

$(OBJ):	$(SRCS) $(LIB)
	gcc -c $(SRCS) -g3

$(LIB):
	make -C libft

clean:
	/bin/rm -f $(OBJ)
	make clean -C libft

fclean: clean
	@/bin/rm -f $(NAME)
	make fclean -C libft

re: fclean all
