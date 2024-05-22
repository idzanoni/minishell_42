#include "minishell.h"

void	command_exec(char **splited_prompt, char **envp)
{
	int 	fork_return;
	char	*path;

	fork_return = fork();
	if (fork_return == -1)
		return ;
	if (fork_return == 0)
	{
		path = find_path(splited_prompt[0], envp);
		if (path == NULL)
		{
			printf("command not found\n");
			free_all(splited_prompt);
			exit(142);
		}
		execve(path, splited_prompt, envp);
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
