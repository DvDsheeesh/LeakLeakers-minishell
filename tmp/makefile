NAME = minishell

CC = cc
CFLAGS = -g -Werror #-Wall #-Wextra

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC =	utils.c \
		tokenize.c \
		cmd_list.c \
		env.c \
		debug.c \
		main.c

OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)

all: $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -lreadline $(OBJ) $(LIBFT) -o $(NAME)

2: $(OBJ2) $(LIBFT)
	$(CC) $(CFLAGS) -lreadline $(OBJ2) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make bonus -C $(LIBFT_DIR)

rerun: all
	valgrind -s --leak-check=full --track-origins=yes ./minishell

fclean:
	rm -f $(OBJ) $(NAME)
	@make fclean -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean

re: fclean all

.PHONY: all rerun clean fclean re