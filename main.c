#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"

struct sfd_in_out
{
	int fd_in;
	int fd_out;
}; 

typedef struct sfd_in_out t_fds;;


void	make_command(char *prompt, char **envp);
char	*find_path(char *splited_prompt, char **envp);
int		is_builtin(char *splited_prompt);
char	*return_value(char **envp, char *var);
int		input_check(char *prompt);
char 	**remove_redirect(char **splited_prompt);
void	mult_command(char **prompt_pipe, char **envp);

void	minishell(char **envp)
{
	char	*prompt;
	char	**prompt_pipe;
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
		// heredoc();
		prompt_pipe = ft_split(prompt, '|');
		// command_sep();
		if (prompt_pipe[1])
		{
			mult_command(prompt_pipe, envp);
		}		
		else
			make_command(prompt, envp);
		printf("-------------\n");
	}
}

int	input_check(char *prompt)
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
} */

void	mult_command(char **prompt_pipe, char **envp)
{
	int	pipe_fds[2];
	int	fork_mult;

	pipe(pipe_fds);
	fork_mult = fork();
	if (fork_mult == 0)
	{
		dup2(pipe_fds[1], 1);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		make_command(prompt_pipe[0], envp);
		exit(0);
	}
	wait(NULL);
	fork_mult = fork();
	if (fork_mult == 0)
	{
		dup2(pipe_fds[0], 0);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		make_command(prompt_pipe[1], envp);
		exit(0);
	}
	wait(NULL);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
}


char	**remove_redirect(char **splited_prompt)
{
	int 	count_line;
	int 	redirect_count;
	char	**return_redirect;

	count_line = 0;
	redirect_count = 0;

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
	count_line = 0;
    while (splited_prompt[count_line] != NULL)
    {
        if(splited_prompt[count_line][0] == '<' || splited_prompt[count_line][0] == '>')
        {
            int copy_count = count_line;
            while (splited_prompt[copy_count] != NULL)
            {
                splited_prompt[count_line] = splited_prompt[count_line + 1];
                copy_count++;
            }
        }
        count_line++;
    }
	return(return_redirect);
}

t_fds	check_redirect(char **redirect)
{
	int	redirect_count;
	t_fds command_fd;

	command_fd.fd_in = 0;
	command_fd.fd_out = 1;
	redirect_count = 0;
	while (redirect[redirect_count] != NULL)
	{
		if (redirect[redirect_count][0] == '>') //out
		{
			if (command_fd.fd_out != 1)
				close(command_fd.fd_out);
			command_fd.fd_out = open(&redirect[redirect_count][1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		else if (redirect[redirect_count][0] == '<') //in
		{
			if (command_fd.fd_in != 0)
				close(command_fd.fd_in);
			command_fd.fd_in = open(&redirect[redirect_count][1], O_RDONLY);
		}
		redirect_count++;
	}
	return (command_fd);
}

void	make_command(char *prompt, char **envp)
{
	char 	**splited_prompt;
	char	*path_founded;
	int		retorno_do_fork;
	char	**redirect;
	t_fds	command_fd;

	splited_prompt = ft_split(prompt, ' ');
	redirect = remove_redirect(splited_prompt);
	command_fd = check_redirect(redirect);
/* 	for (int i = 0; redirect[i] != NULL; i++)
		printf("%s\n", redirect[i]);
	return; */

	//remove_redirect(); // echo oi >arquivo <arquivo
	//
	//expand_remove_quote();
	if (is_builtin(splited_prompt[0]) == 1)
	{
		exit(1);
		//exec_builtin(splited_prompt);
	}
	else
	{
		path_founded = find_path(splited_prompt[0], envp);
		retorno_do_fork = fork();
		if (retorno_do_fork == 0)
		{
			if (command_fd.fd_in != 0)
				dup2(command_fd.fd_in, 0);
			if (command_fd.fd_out != 1)
				dup2(command_fd.fd_out, 1);
			execve(path_founded, splited_prompt, envp);
			exit(0);
		}
		wait(NULL);
	}
}

char	*find_path(char *splited_prompt, char **envp)
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
		if (access(path, F_OK) == 0)
			return(path);
		i++;
	}
	return(NULL);
}

int	is_builtin(char *splited_prompt)
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
char	*return_value(char **envp, char *var)
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

int	main(int argc, char **argv, char **envp)
{
	minishell(envp);
	return(0);
}
