
FILES		=	$(addsuffix .c, minishell_real_oficial_agora_vai)

FLAGS		=	-Wall -Wextra -Werror

all:
	cc $(FLAGS) $(FILES) -l readline -o minishell