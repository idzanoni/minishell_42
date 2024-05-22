
FILES		=	$(addsuffix .c, minishell_real_oficial_agora_vai \
					check_things free_all new_split execv funcitions ft_split)

FLAGS		=	-Wall -Wextra -Werror

all:
	cc $(FLAGS) $(FILES) -l readline -o minishell