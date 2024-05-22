#include "minishell.h"

void	command_exec(char **splited_prompt, char **envp)
{
	int 	fork_return;
	char	*path;

	fork_return = fork();
	if (fork_return == -1)
		return;
	if (fork_return == 0)
	{
		path = find_path(splited_prompt[0], envp);
		execve(path, splited_prompt, envp);
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
	int		i;

	i = 0;
	path_env = return_value(envp, "PATH");
	splited_path = ft_split(path_env, ':');
	if ()
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