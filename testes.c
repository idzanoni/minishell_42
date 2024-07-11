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

void minishell(t_minishell *s_minishell)
{
	while (1)
	{
		s_minishell->input = readline("shellzinho: ");
		if (!s_minishell->input)
		{
			free_list(s_minishell->envp);
			break;
		}
		process_input(s_minishell);
	}
}
void process_input(t_minishell *s_minishell)
{
	if (check_prompt(s_minishell->input) < 0)
	{
		free(s_minishell->input);
		return;
	}
	s_minishell->normalized_prompt = norme_string(s_minishell->input);
	free(s_minishell->input);
	if (!s_minishell->normalized_prompt)
	{
		printf("error\n");
		return;
	}
	new_prompt(s_minishell->normalized_prompt);
	s_minishell->splited_prompt = ft_split(s_minishell->normalized_prompt, -42);
	free(s_minishell->normalized_prompt);
	if (!s_minishell->splited_prompt)
	{
		printf("error\n");
		return;
	}
	handle_commands(s_minishell);
	free_all(s_minishell->splited_prompt);
}

void handle_commands(t_minishell *s_minishell)
{
	if (check_heredoc(s_minishell->splited_prompt) == 1)
	{
		heredoc(s_minishell);
	}
	if (find_pipe(s_minishell->splited_prompt) == 1)
	{
		//printf("entrei\n");
		more_command(s_minishell);
	}
	else
	{
		s_minishell->current_command = s_minishell->splited_prompt;
		s_minishell->splited_prompt = NULL;
		bt_or_exec(s_minishell);
	}
}
