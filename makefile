NAME = minishell

CC = cc
CFLAGS = -g -Werror #-Wall #-Wextra

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = parsing/parse_input.c
SRC2 =	execution/utilz.c \
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
		parsing/parse_input_2.c

OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)

all: $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
# 	$(CC) $(CFLAGS) -lreadline $(OBJ) $(LIBFT) -o $(NAME)

2: $(OBJ2) $(LIBFT)
	$(CC) $(CFLAGS) -lreadline $(OBJ2) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) bonus

rerun: all
	valgrind -s --leak-check=full --track-origins=yes ./minishell

rerun2: 2
	valgrind -s --leak-check=full --track-origins=yes ./minishell

fclean:
	rm -f $(OBJ) $(NAME)
	@make fclean -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean

re: fclean all

.PHONY: all rerun clean fclean re