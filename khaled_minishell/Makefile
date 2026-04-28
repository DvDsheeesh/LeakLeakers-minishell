CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = shellwedance

ERRORS = errors/check_syntax_errors.c errors/error_handling.c

EXECUTION = execution/builtins_basic.c execution/builtins_cd.c \
	execution/builtins_dispatcher.c execution/builtins_exit.c \
	execution/builtins_export.c execution/builtins_unset.c \
	execution/env_to_char_array.c execution/env_utils.c \
	execution/executor_child.c execution/executor_utils.c \
	execution/executor.c execution/get_cmd_path.c \
	execution/handle_redirections.c execution/init_env.c

SIGNALS = signals/signals_heredoc.c signals/signals.c

EXPANDER = expander/expander1.c expander/expander2.c

LISTS = lists/commands_list.c lists/env_list.c lists/files_list.c \
	lists/tokens_list.c

MEMORY_MANAGMENT = memory_managment/destroy_program_info1.c \
		memory_managment/destroy_program_info2.c \
		memory_managment/manage_program_info.c

PARSER = parser/parse_heredoc1.c parser/parse_heredoc2.c \
	parser/parser.c

TOKENIZER = tokenizer/tokenizer_cleanup.c tokenizer/tokenizer1.c \
	tokenizer/tokenizer2.c

MAIN = main.c

OBJ	= $(ERRORS:.c=.o) $(EXECUTION:.c=.o) $(SIGNALS:.c=.o) \
	 $(EXPANDER:.c=.o) $(LISTS:.c=.o) $(MEMORY_MANAGMENT:.c=.o) \
	 $(PARSER:.c=.o) $(TOKENIZER:.c=.o) $(MAIN:.c=.o)

LIBFT = libft/libft.a

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
