NAME = minishell

CC = cc
CFLAGS = -g -Werror #-Wall #-Wextra

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = parse_input.c

OBJ = $(SRC:.c=.o)

all: $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -lreadline $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

rerun:
	valgrind -s --leak-check=full --track-origins=yes ./minishell

fclean:
	rm -f $(OBJ) $(NAME)
	@make fclean -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean

re: fclean all

.PHONY: all rerun clean fclean re