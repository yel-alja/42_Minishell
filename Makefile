CC = cc

CFLAGS = -g

SRC = $(SRC_BUILT_IN) $(SRC_PARS) $(SRC_EXEC) main.c
SRC_EX_DIR = src/execution
SRC_PAR_DIR = src/parsing

SRC_BUILT_IN = $(SRC_EX_DIR)/built-in/ft_cd.c $(SRC_EX_DIR)/built-in/ft_pwd.c \
				$(SRC_EX_DIR)/built-in/ft_export.c $(SRC_EX_DIR)/built-in/ft_env.c \
				$(SRC_EX_DIR)/built-in/ft_unset.c $(SRC_EX_DIR)/built-in/ft_exit.c \
				$(SRC_EX_DIR)/built-in/ft_echo.c

SRC_EXEC = $(SRC_EX_DIR)/execution.c $(SRC_EX_DIR)/redirection.c $(SRC_EX_DIR)/utils.c $(SRC_EX_DIR)/envp.c

SRC_PARS = $(SRC_PAR_DIR)/tokenizer.c  $(SRC_PAR_DIR)/garbage_collector.c $(SRC_PAR_DIR)/utils.c \
			$(SRC_PAR_DIR)/syntax.c $(SRC_PAR_DIR)/expansion.c

LIB = libft/libft.a

OBJ = $(SRC:.c=.o)

NAME = minishell

all : $(NAME)

$(LIB) :
	make -C libft

$(NAME) : $(OBJ) $(LIB)
	$(CC) $(CFLAGS) -L/usr/lib/x86_64-linux-gnu  $(OBJ) $(LIB) -o $(NAME) -lreadline 


clean :
	rm -rf $(OBJ)
	make -C libft clean

fclean : clean
	rm -rf $(NAME)
	make -C libft fclean

re : fclean all

.PHONY:  all clean fclean re
