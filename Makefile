NAME = minishell

SRCS =  

#OBJS = $(SRCS:.c=.o)


CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RLFLAGS = -lreadline
LIBFT_DIR = libft/
LIBFT = libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)
# $(NAME): $(OBJS)
# $(CC) $(OBJS) $(CFLAGS) $(RLFLAGS) $(LIBFT) -o $(NAME)

clean:
# rm -f $(OBJS) $(BONUS_OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
#rm -f $(NAME) $(BONUS_NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re