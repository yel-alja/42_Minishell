CC = cc

CFLAGS = -g

SRC = $(addprefix src/, $(SRC_EXEC) $(SRC_PARS) main.c)

SRC_BUILT_IN = $(addprefix built-in/, ft_cd.c ft_pwd.c ft_export.c ft_env.c ft_unset.c ft_exit.c ft_echo.c)

SRC_PARS = $(addprefix parsing/,)
SRC_EXEC = $(addprefix execution/, execution.c redirection.c utils.c \
			$(SRC_BUILT_IN))
LIB = libft/libft.a

OBJ = $(SRC:.c=.o)

NAME = minishell

all : $(NAME)

$(NAME) : $(OBJ) $(LIB)
	@$(CC) $(CFLAGS) -lreadline $(OBJ) $(LIB) -o $(NAME)

$(LIB) :
	@make -C libft

clean :
	@rm -rf $(OBJ)
	@make -C libft clean

fclean : clean
	@rm -rf $(NAME)
	@make -C libft fclean

re : fclean all

.PHONY:  all clean fclean re
