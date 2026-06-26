CC = cc
CFLAGS = -g -Werror -Wall -Wextra
NAME = minishell

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC =	signals/signals.c \
		signals/signals_heredoc.c \
		execution/utilz2.c \
		execution/utilz.c \
		execution/pipe.c \
		execution/env_get_path.c \
		execution/env_utils2.c \
		execution/env_utils.c \
		execution/built_in_exec.c \
		execution/builtins.c \
		execution/builtins_env.c \
		execution/builtins_cd.c \
		execution/builtins_exit.c \
		execution/builtins_unset.c \
		execution/executor.c \
		execution/heredoc.c \
		parsing/cmd_utils.c \
		parsing/cmd_process.c \
		parsing/parse_utils.c \
		parsing/split_words.c \
		parsing/join_arg.c \
		parsing/env.c \
		parsing/dollaroze.c \
		parsing/labels.c \
		parsing/vars.c \
		parsing/main.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
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
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes ./minishell

supp:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes --suppressions=readline.supp ./minishell

rerun: re vrun

.PHONY: all clean fclean re run vrun rerun