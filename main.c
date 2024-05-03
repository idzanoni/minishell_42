void minishell(char **envp)
{
	while (42)
	{
		readline();
		input_check();
		heredoc();
		command_sep();
		if (command_sep > 1)
		{
			mult_command();
		}		
		else
			make_command();
		
	}
}

void mult_command()
{
	while(command > 0)
	{
		pipe();
		fork();
		if(child)
		{
			change_fd();
			make_command();
		}
		else
		{
			close_pipe();
		}
		command--;
	}
	wait_child();
}

void make_command()
{
	slip_command();
	remove_redirect();
	check_redirect();
	expand_remove_quote();
	if (is_builtin() == 1)
	{
		exec_builtin();
	}
	else
	{
		find_path();
		execve();
	}
}

void freeeeee()
{
	free;
}

char *return_value(char ** envp, char *var)
{
	PWD=/nfs/homes/izanoni/izabeldz/minishell
	BANANA=É fruta
	
	echo bom dia $PWD Saiba que mamão $BANANA

	bom dia /nfs/homes/izanoni/izabeldz/minishell Saiba que mamão É fruta
0xa0 0xa1 0xa2
	var = "Bom dia Mah!";
	var++;
	char *temp = envp[0];
	char letter = (envp[0])[5];
	"om dia Mah!"
	var[0] = 'o'
	var[1] 'm'  __SIZE_MAX_
	var[2] ' '
	var[3] 'd'
	if (var[4] == 'j')
	var -> "ia Mah!"
	printf ("%s\n", var);
	
	
	char *value;
	strnstr (final+1 '=')
	//encontrar a variavel no envp, texto igual, apos final da palavra ser =, retornar tudo até '\0'
	return();
	
}

int main(int argc, char **argv, char **envp)
{
	minishell(envp);
	return(0);
}
