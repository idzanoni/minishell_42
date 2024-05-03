#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <sys/wait.h>

void minishell(char **envp)
{
	char *prompt;

	while (42)
	{
		prompt = readline("Shellzinho:");
		/* input_check();
		heredoc();
		command_sep();
		if (command_sep > 1)
		{
			mult_command();
		} */		
		//else
			make_command(prompt, envp);
		
	}
}

/* void mult_command()
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
 */
void make_command(char *prompt, char *envp)
{
	char 	**splited_prompt;
	char	*path_founded;

	splited_prompt = ft_split(prompt, ' ');
	//remove_redirect();
	//check_redirect();
	//expand_remove_quote();
	if (is_builtin(splited_prompt[0]) == 1)
	{
		exit(1);
		//exec_builtin();
	}
	else
	{
		path_founded = find_path(splited_prompt[0], envp);
		// Find path retornou o caminho, agora é só mandar pro execve com
	// O comando e o envp
	// Vou jantar e já volto.
	// Com isso já dá para executar 1 comando
	// Se colocar o fork, vai dar pra executar vários commandos	
		execve(path_founded, splited_prompt[0], envp);
	}
}

char *find_path(char *splited_prompt, char **envp)
{
	char	*path;
	char	*path_env;
	char	**splited_path;
	int		i;

	i = 0;
	path_env = return_value(envp, "PATH");
	splited_path = ft_split(path_env, ':');
	while(splited_path[i] != NULL)
	{
		path = ft_join(splited_path[i], "/");
		path = ft_join(path, splited_prompt);
		if (access(path, F_OK))
			return(path);
		i++;
	}
	return(NULL);
}

int is_builtin(char *splited_prompt)
{
	if (ft_strnstr(splited_prompt, "exit", 4) != NULL)
		return (1);
	else
		return (0);
}

void freeeeee()
{
	free;
}

char *return_value(char **envp, char *var)
{
	char	*value;
	int		len_var;
	int		i;

	i = 0;
	len_var = ft_strlen(var);
	while(envp[i] != NULL)
	{
		value = ft_strnstr (envp[i], var, len_var);
		if(value != NULL)
		{
			if (envp[i][len_var] == "=")
				return(&envp[i][len_var + 1]);
		}
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv, char **envp)
{
	minishell(envp);
	return(0);
}
