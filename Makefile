NAME = minishell

FILES = $(addsuffix .c, minishell_real_oficial_agora_vai \
		check_things free_all new_split execv funcitions ft_split builtins bt_export)

FLAGS = -Wall -Wextra -Werror -g3

all:
	cc $(FLAGS) $(FILES) -l readline -o $(NAME)

v: all
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --trace-children-skip=''*/bin/*,*/sbin/*'' --keep-debuginfo=yes \
	--suppressions=leak_readline --track-fds=yes ./$(NAME)