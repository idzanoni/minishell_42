NAME = minishell

FILES = $(addsuffix .c, minishell_real_oficial_agora_vai \
		bt_cd bt_exit bt_unset expand_var free_all bt_echo bt_export check_things \
		expandvar ft_split redirect bt_env	bt_pwd	execv new_split)
		
FLAGS = -Wall -Wextra -Werror -g3

all:
	cc $(FLAGS) $(FILES) -l readline -o $(NAME)

v: all
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --trace-children-skip=''*/bin/*,*/sbin/*'' --keep-debuginfo=yes \
	--suppressions=leak_readline --track-fds=yes ./$(NAME)