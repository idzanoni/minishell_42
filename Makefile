# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/20 17:13:45 by izanoni           #+#    #+#              #
#    Updated: 2024/07/16 19:56:11 by izanoni          ###   ########.fr        #
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
			bt_echo \
			bt_pwd \
			check_input \
			exec_commnad \
			exec_command2 \
			init_minishell \
			redirect \
			expand_var \
			expand_var2 \
			t_list_functions \
			signals \
			heredoc \
			norme_prompt\
			check_command\
			envp_funcitions\
			utils_functions\
			bt_exit)
			 
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