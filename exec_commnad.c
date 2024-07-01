/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commnad.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:13:41 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/01 19:31:29 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **execve_envp(t_env_list *envp)
{
	char    **other_envp;
	t_env_list  *tmp;
	int i;

	tmp = envp;
	i = ft_lstsize(tmp);
	other_envp = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (tmp != NULL)
	{
		other_envp[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	other_envp[i] = NULL;
	return (other_envp);
}

void	command_exec(t_minishell *s_minishell, t_fds fd_redirect)
{
	int		fork_return;
	char	*path;

	fork_return = fork();
	if (fork_return == -1)
		return ;
	if (fork_return == 0)
	{
		rl_clear_history();
		path = find_path(s_minishell->splited_prompt[0], s_minishell->envp);
		if (path == NULL)
		{
			printf("command not found\n");
			free_all(s_minishell->splited_prompt);
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
		execve(path, s_minishell->splited_prompt, execve_envp(s_minishell->envp));
		free_all(s_minishell->splited_prompt);
		free(path);
		exit(142);
	}
	else
	{
		wait(NULL);
	}
}

char	*find_path(char *splited_prompt, t_env_list *envp)
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
		free (path);
		i++;
	}
	free_all(splited_path);
	return (NULL);
}

char	*return_value(t_env_list    *envp, char *var)
{
	char	*value;
	int		len_var;
	t_env_list  *tmp;

	len_var = ft_strlen_2(var);
	tmp = envp;
	while (tmp != NULL)
	{
		value = ft_strnstr (tmp->content, var, len_var);
		if (value != NULL)
		{
			if (tmp->content[len_var] == '=')
				return (&tmp->content[len_var + 1]);
			if (tmp->content[len_var] == '\0')
				return (&tmp->content[len_var]);
		}
		tmp = tmp->next;
	}
	return (NULL);
}


void    more_command(t_minishell *s_minishell)
{
	int count_pipes;
	int i;
	int j;
	int fds[2];
	int    fd_bkp;
	int    *fork_return;

	count_pipes = 0;
	i = 0;
	j = 0;
	while(s_minishell->splited_prompt[i] != NULL)
	{
		if(s_minishell->splited_prompt[i][0] == '|')
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
			s_minishell->current_command = get_command(s_minishell->splited_prompt);
			free_all (s_minishell->splited_prompt);
			if (count_pipes > 0) // Mudei apenas para que fique mais visual o que ocorre no comando
			{
				dup2 (fds[1], STDOUT_FILENO);
				close (fds[1]);
				close (fds[0]);
			}
			dup2 (fd_bkp, STDIN_FILENO);
			if (fd_bkp != 0) // Idem por aqui
				close (fd_bkp);
			bt_or_exec(s_minishell);
			close(STDIN_FILENO); // Esse close
			close(STDOUT_FILENO); // E esse aqui, são para evitar fds abertos
			free_all(s_minishell->current_command);
			exit(142);
		}
		else
		{
			free_all(get_command(s_minishell->splited_prompt)); // Precisa desse free no pai
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
