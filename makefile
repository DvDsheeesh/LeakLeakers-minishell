NAME = minishell

CC = cc
CFLAGS = -g -Werror #-Wall -Wextra

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC =	execution/utilz.c \
		execution/env_get_path.c \
		execution/env_utils.c \
		execution/built_in_exec.c \
		execution/builtins.c \
		execution/builtins_env.c \
		execution/builtins_cd.c \
		execution/builtins_exit.c \
		execution/builtins_unset.c \
		execution/parser.c \
		execution/executor.c \
		parsing/parse_input.c

OBJ = $(SRC:.c=.o)

all: $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	@make -C $(LIBFT_DIR) bonus

fclean:
	rm -f $(OBJ) $(NAME)
	@make fclean -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean

re: fclean all

run: all
	./$(NAME)

vrun:
	valgrind -s --leak-check=full --track-origins=yes ./minishell

rerun: re vrun

.PHONY: all rerun clean fclean re