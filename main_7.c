#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include "libft/libft.h"


void	make_command(char *prompt, char **envp);
char	*find_path(char *splited_prompt, char **envp);
int		is_builtin(char *splited_prompt);
char	*return_value(char **envp, char *var);
int		input_check(char *prompt);

void minishell(char **envp)
{
	char	*prompt;
	int		check;

	while (42)
	{
		prompt = readline("Shellzinho:");
		check = input_check(prompt);
		if (check != 0)
		{
			if (check == 2)
				continue ; //reset de while
			if (check == 1)
				break ;
		}
		// >arquivo
		/* heredoc();
		command_sep();
		if (command_sep > 1)
		{
			mult_command();
		} */		
		//else
		make_command(prompt, envp);
		printf("-------------\n");
	}
}

int 		input_check(char *prompt)
{
	//é uma verificação estrutural
	//string vazia (só \0 e ctrl+d(nula)), aspas, dados completos << |
	if (prompt == NULL)
	{
		return(1);
	}
	if (prompt[0] == '\0')
	{
		return(2);
	}

	return(0);
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

char **remove_redirect(char **splited_prompt)
{
	int 	count_line;
	int 	redirect_count;
	char	**return_redirect;

	count_line = 0;
	redirect_count = 0;
	/* splited_prompt
	[0] echo
	[1] >arquivo
	[2] oi
	[3] <arquivo
	NULL
	*/
/* retorno
	[0] >arquivo
	[1] <arquivo
	NULL
*/
	while(splited_prompt[count_line] != NULL)
	{
		if(splited_prompt[count_line][0] == '<' || splited_prompt[count_line][0] == '>')
			redirect_count++;
		count_line++;	
	}
	return_redirect = malloc((redirect_count + 1 ) * sizeof(char*));
	count_line = 0;
	redirect_count = 0;
	while(splited_prompt[count_line] != NULL)
	{
		if(splited_prompt[count_line][0] == '<' || splited_prompt[count_line][0] == '>')
		{
			return_redirect[redirect_count] = ft_strdup(splited_prompt[count_line]);
			redirect_count++;
		}
		count_line++;	
	}
	return_redirect[redirect_count] = NULL;
	return(return_redirect);
}

void make_command(char *prompt, char **envp)
{
	char 	**splited_prompt;
	char	*path_founded;
	int		retorno_do_fork;
	char	**redirect;

	splited_prompt = ft_split(prompt, ' ');
	redirect = remove_redirect(splited_prompt);
	for (int i = 0; redirect[i] != NULL; i++)
		printf("%s\n", redirect[i]);
	return;

	//remove_redirect(); // echo oi >arquivo <arquivo
	//
	//check_redirect();
	//expand_remove_quote();



	if (is_builtin(splited_prompt[0]) == 1)
	{
		exit(1);
		//exec_builtin(splited_prompt);
	}
	else
	{
		path_founded = find_path(splited_prompt[0], envp);
		// Find path retornou o caminho, agora é só mandar pro execve com
	// O comando e o envp
	// Vou jantar e já volto.
	// Com isso já dá para executar 1 comando
	// Se colocar o fork, vai dar pra executar vários commando
		retorno_do_fork = fork();
		if (retorno_do_fork == 0)
		{	
			execve(path_founded, splited_prompt, envp);
			exit(0);
		}
		wait(NULL);
		printf("make: %s e %s\n", path_founded, splited_prompt[0]);
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
		path = ft_strjoin(splited_path[i], "/");
		path = ft_strjoin(path, splited_prompt);
		//path = ft_strjoin("/bin/", splited_prompt);
		if (access(path, F_OK) == 0)
			return(path);
		i++;
	}
	return(NULL);
/* 	PATH=/nfs/homes/izanoni/bin
	:/nfs/homes/izanoni/bin
	:/usr/local/sbin
	:/usr/local/bin
	:/usr/sbin
	:/usr/bin
	:/sbin
	:/bin
	:/usr/games
	:/usr/local/games
	:/snap/bin */
}

int is_builtin(char *splited_prompt)
{
	if (ft_strnstr(splited_prompt, "exit", 4) != NULL)
		return (1);
	else
		return (0);
}

/* void freeeeee()
{
	free;
}
 */
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
			if (envp[i][len_var] == '=')
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

