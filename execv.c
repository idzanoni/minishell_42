#include "minishell.h"

void	command_exec(char **splited_prompt, char **envp, t_fds fd_redirect)
{
	int		fork_return;
	char	*path;

	fork_return = fork();
	if (fork_return == -1)
		return ;
	if (fork_return == 0)
	{
		rl_clear_history();
		path = find_path(splited_prompt[0], envp);
		if (path == NULL)
		{
			printf("command not found\n");
			free_all(splited_prompt);
			exit(142);
		}
		if (fd_redirect.fd_in != STDIN_FILENO)
		{
			dup2 (fd_redirect.fd_in, STDIN_FILENO);
			close (fd_redirect.fd_in);
		}
		if (fd_redirect.fd_out != STDOUT_FILENO)
		{
			dup2 (fd_redirect.fd_out, STDOUT_FILENO);
			close (fd_redirect.fd_out);
		}
		execve(path, splited_prompt, envp);
		free_all(splited_prompt);
		free(path);
		exit(142);
	}
	else
	{
		wait(NULL);
	}
}

char	*find_path(char *splited_prompt, char **envp)
{
	char	*path;
	char	*path_env;
	char	**splited_path;
	char 	*temp;
	int		i;

	i = 0;
	if (ft_strchr(splited_prompt, '/') != NULL)
		return (splited_prompt);
	path_env = return_value(envp, "PATH");
	splited_path = ft_split(path_env, ':');
	if (!splited_path)
		return (NULL);
	while (splited_path[i] != NULL)
	{
		temp = ft_strjoin(splited_path[i], "/");
		if (!temp)
			break ;
		path = ft_strjoin(temp, splited_prompt);
		free(temp);
		if (!path)
			break ;
		if (access(path, F_OK) == 0)
		{	
			free_all(splited_path);
			return (path);
		}
		i++;
	}
	free_all(splited_path);
	return(NULL);	
}

char	*return_value(char **envp, char *var) //grep
{
	char	*value;
	int		len_var;
	int		i;

	i = 0;
	len_var = ft_strlen(var);
	while (envp[i] != NULL)
	{
		value = ft_strnstr (envp[i], var, len_var);
		if (value != NULL)
		{
			if (envp[i][len_var] == '=')
				return (&envp[i][len_var + 1]);
		}
		i++;
	}
	return (NULL);
}

/****
 pipe(int[2])
 int fd0 = open(file, O_RDONLY);
 int fd1 = open(file, O_WRONLY);
 int[fd0, fd1]      int[fd0, fd1]
 fork()
 if (fork_ret == 0)
 {
	int[0]
	int[1]
 }

 int[0]
 int[1]

 int pipes[2];

 pipe(pipes);
 fork()

 if ( == 0)
 {
	pipes[0]
	pipes[1]
 }
 else
 {
	pipes[0]
	pipes[1]
 }

 echo oi | ls | cat | grep word | echo como estamos
0 ---------->---->------>---->---------------------> 1

0 echo oi | ls | cat | grep word | echo como estamos 1

0 echo oi 3|4 ls 5|6 cat 7|8 grep word 9|10 echo como estamos 1


R         R W    R W     R W           R W                    W
0 echo oi 3|4 ls 5|6 cat 7|8 grep word 9|10 echo como estamos 1

 */

void    more_command(char **splited_prompt, char **envp)
{
    int count_pipes;
    int i;
    int j;
    int fds[2];
    int    fd_bkp;
    int    *fork_return;
    char    **current_command;

    count_pipes = 0;
    i = 0;
    j = 0;
    while(splited_prompt[i] != NULL)
    {
        if(splited_prompt[i][0] == '|')
            count_pipes++;
        i++;
    }
    fd_bkp = STDIN_FILENO;
    fork_return = malloc((count_pipes + 2) * sizeof(int));
    if (!fork_return)
    {}
    while(count_pipes >= 0)
    {
        if (count_pipes > 0)
            pipe(fds);
        fork_return[j] = fork();
        if (fork_return[j] == 0)
        {
            rl_clear_history();
            free(fork_return);
            current_command = get_command(splited_prompt);
            free_all (splited_prompt);
            if (count_pipes > 0) // Mudei apenas para que fique mais visual o que ocorre no comando
            {
                dup2 (fds[1], STDOUT_FILENO);
                close (fds[1]);
                close (fds[0]);
            }
            dup2 (fd_bkp, STDIN_FILENO);
            if (fd_bkp != 0) // Idem por aqui
                close (fd_bkp);
            bt_or_exec(current_command, envp);
            close(STDIN_FILENO); // Esse close
            close(STDOUT_FILENO); // E esse aqui, são para evitar fds abertos
            free_all(current_command);
            exit(142);
        }
        else
        {
            free_all(get_command(splited_prompt)); // Precisa desse free no pai
            if (fd_bkp != STDIN_FILENO)
                close (fd_bkp);
            fd_bkp = fds[0];
            if (count_pipes > 0)
                close (fds[1]);
            count_pipes--;
            j++;
        }
    }
    fork_return[j] = -42; // Colocar o "rabba zero" do array
    i = 0;
    while (fork_return[i] != -42)
    {
        waitpid(fork_return[i], NULL, 0);
        i++;
    }
    free(fork_return); // free no array (não precisamos mais dele agora)
}

char **get_command(char **splited_prompt)
{
    int i;
    int count_lines;
    char **command;
    
    i = 0;
    count_lines = 0;
    while(splited_prompt[i] != NULL)
    {
        if(splited_prompt[i][0] == '|')
            break ;
        count_lines++;
        i++;
    }
    command = malloc ((count_lines + 1) * sizeof(char *));
    if (!command)
        return (NULL);
    free(splited_prompt[i]); // Dar free no pipe (sem isso dá leak)
    i = 0;
    while (i < count_lines)
    {
        command[i] = splited_prompt[i];
        i++;
    }
    command[i] = NULL;
    i = 0;
    while (splited_prompt[count_lines] != NULL)
    {
        splited_prompt[i++] = splited_prompt[++count_lines];
    }
    splited_prompt[i] = NULL;
    return (command);
}
