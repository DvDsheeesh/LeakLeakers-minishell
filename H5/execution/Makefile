CC		= cc
CFLAGS	= -Wall -Wextra -Werror
NAME	= minishell

SRCS	= main.c \
		  utilz.c \
		  env_get_path.c \
		  env_utils.c \
		  built_in_exec.c \
		  builtins.c \
		  builtins_env.c \
		  builtins_cd.c \
		  builtins_exit.c \
		  builtins_unset.c \
		  parser.c \
		  executor.c \
		  pipe.c


OBJ		= $(SRCS:.c=.o)
LIBFT	= libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline libft/libft.a -o $(NAME)

$(LIBFT):
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
