NAME = minishell
#SRCS = minishell.c get_next_line.c
SRCS = test.c
LIB = libft/libft.a
OBJ = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror -g3

all:	$(NAME)

$(NAME): $(OBJ) $(LIB)
	gcc -o $(NAME) $(FLAGS) $(OBJ) -L. $(LIB)

$(OBJ):	$(SRCS) $(LIB)
	gcc -c $(SRCS)

$(LIB):
	make -C libft

clean:
	/bin/rm -f $(OBJ)
	make clean -C libft

fclean: clean
	@/bin/rm -f $(NAME)
	make fclean -C libft

re: fclean all