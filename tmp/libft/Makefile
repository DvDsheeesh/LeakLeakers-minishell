# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melshata <melshata@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/14 18:51:27 by melshata          #+#    #+#              #
#    Updated: 2026/01/12 11:19:52 by melshata         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CGNL =	get_next_line.c \
		get_next_line_utils.c

CBONUS =	ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c

CFILES =	ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_striteri.c

NAME = libft.a
CC = cc
CFLAGS = -Werror -Wall -Wextra
OBJ := $(CFILES:.c=.o)
OBJbonus := $(CBONUS:.c=.o)
OBJgnl := $(CGNL:.c=.o)

ifneq (,$(filter bonus,$(MAKECMDGOALS)))
	OBJ += $(OBJbonus)
endif

ifneq (,$(filter gnl,$(MAKECMDGOALS)))
	OBJ += $(OBJgnl)
endif

ifneq (,$(filter full,$(MAKECMDGOALS)))
	OBJ += $(OBJbonus) $(OBJgnl)
endif

all: $(NAME)

full: fclean gnl
	
$(NAME):$(OBJ)
	ar rcs $(NAME) $(OBJ)

fclean:
	rm -f $(OBJ) $(NAME) $(OBJbonus) $(OBJgnl)

clean:
	rm -f $(OBJ) $(OBJbonus)

bonus : all

gnl : all

# bonus: $(OBJ) $(OBJbonus)
# 	ar rcs $(NAME) $(OBJ) $(OBJbonus)

# gnl: $(OBJ) $(OBJbonus) $(OBJgnl)
# 	ar rcs $(NAME) $(OBJ) $(OBJbonus) $(OBJgnl)

re: fclean all

.PHONY: all clean fclean re bonus

norm: $(CFILES)
	norminette $(CFILES) libft.h

testt: full fclean

testm:$(OBJ) $(OBJbonus)
	cc $(OBJ) $(OBJbonus) $(CFLAGS)
