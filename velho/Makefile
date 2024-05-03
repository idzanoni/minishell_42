# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/21 12:23:17 by izanoni           #+#    #+#              #
#    Updated: 2024/05/02 16:32:53 by izanoni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -c
AR = ar rcs

FILES = ft_printf.c handle_char_str.c handle_num.c

OBJ = $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
