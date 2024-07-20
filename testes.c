echo oi <                  
echo oi <<         
echo oi >
echo oi >>        
| echo oi
echo oi |
echo oi |         
echo oi > | ls
echo oi > file | ls |
echo oi > file | ls |       
echo oi |        | ls
echo "oi" 'mundo
echo 'o" 'i"
echo "c"'o'"m'"'o' "v"'ai 'm"u"n''''"d'"ão''"?
echo "oi    mundo">file|ls

		// errado
		|
		| echo oi
		echo oi |
		| |
		echo oi "> file | ls" | ls |      
		           | echo oi
		echo oi |        | ls

		// correto
		ls | echo
		ls | > file
		ls|>file
		echo | echo | << file | echo

"
bt_cd.c
bt_cd.o
bt_echo.c
bt_echo.o
bt_env.c
bt_env.o
bt_exit.c
bt_exit.o
bt_export.c
bt_export.o
bt_pwd.c
bt_pwd.o
bt_unset.c
bt_unset.o
check_command.c
check_command.o
check_input.c
check_input.o
envp_funcitions.c
envp_funcitions.o
error.c
error.o
exec_command2.c
exec_command2.o
exec_commnad.c
exec_commnad.o
expand_var2.c
expand_var2.o
expand_var.c
expand_var.o
free_all.c
free_all.o
heredoc.c
heredoc.o
init_minishell.c
init_minishell.o
leak_readline
libft
Makefile
minishell
minishell.h
more_command.c
norme_prompt.c
norme_prompt.o
redirect.c
redirect.o
signals.c
signals.o
testes.c
t_list_functions.c
t_list_functions.o
to_do.txt
utils_functions2.c
utils_functions2.o
utils_functions.c
utils_functions.o
