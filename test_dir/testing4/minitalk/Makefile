NAME_server = server
NAME_client = client

CC = cc
CFLAGS = -g -Werror -Wall -Wextra
INCLUDES = -I./ -Ift_printf -Isystem

FT_PRINTF_DIR = ./ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

SRC_server = system/server.c
SRC_client = system/client.c

OBJ_server = $(SRC_server:.c=.o)
OBJ_client = $(SRC_client:.c=.o)

all: $(NAME_server) $(NAME_client)

$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR)

$(NAME_server): $(OBJ_server) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJ_server) $(FT_PRINTF) -o $(NAME_server)

$(NAME_client): $(OBJ_client) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJ_client) $(FT_PRINTF) -o $(NAME_client)

clean:
	rm -f $(OBJ_server) $(OBJ_client)
	@make -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME_server) $(NAME_client)
	@make fclean -C $(FT_PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re
