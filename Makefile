# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/20 17:13:45 by izanoni           #+#    #+#              #
#    Updated: 2024/06/24 15:25:07 by mgonzaga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror -g3 -I$(LIBFT)
RM = rm -f

LIBFT = ./libft

FILES = $(addsuffix .c, bt_cd\
			bt_env \
			bt_export \
			bt_unset \
			error \
			free_all \
			new_split \
			bt_echo \
			bt_exit \
			bt_pwd \
			check_things \
			execv \
			ft_split \
			minishell_real_oficial_agora_vai \
			redirect \
			funcitions \
			expand_var\
			heredoc)
			
OBJ = $(FILES:%.c=%.o)			

all: libs $(NAME)
	
$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT)/libft.a -l readline -o $(NAME)

libs:
	@make -C $(LIBFT) --silent

v: all
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --trace-children-skip=''*/bin/*,*/sbin/*'' --keep-debuginfo=yes \
	--suppressions=leak_readline --track-fds=yes ./$(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFT)
	@$(RM)  $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re libs v