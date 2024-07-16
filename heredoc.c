/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:10:52 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/16 17:23:56 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_with_empty_strings(char **heredoc_name, int size)
{
	int	count;

	count = 0;
	while (count < size - 1)
	{
		heredoc_name[count] = ft_strdup("");
		count++;
	}
	heredoc_name[count] = NULL;
}

char	*get_heredoc_name(void)
{
	static int	heredoc_number;
	char		*string_of_heredoc_number;
	char		*name;

	string_of_heredoc_number = ft_itoa(heredoc_number);
	if (string_of_heredoc_number == NULL)
   {}
	heredoc_number++;
	name = ft_strjoin("/tmp/heredoc", string_of_heredoc_number);
	if (name == NULL)
	{}
	free(string_of_heredoc_number);
	return (name);
}

int 	heredoc(t_minishell *s_minishell)
{
	int	count;
	int	count_command;
	int	fd;

	sig_heredoc();
	count = pipes_count(s_minishell->splited_prompt);
	s_minishell->heredoc_names = malloc((count + 2) * sizeof(char *));
	initialize_with_empty_strings(s_minishell->heredoc_names, count + 2);
	count = 0;
	count_command = 0;
	while (s_minishell->splited_prompt[count] != NULL)
	{
		if (s_minishell->splited_prompt[count][0] == '|')
			count_command++;
		if (s_minishell->splited_prompt[count][0] == '<'
		&& s_minishell->splited_prompt[count][1] == '<')
		{
			if(heredoc_process(&count, s_minishell,
				&count_command, &fd) == 1)
			{
				free_heredoc_names(s_minishell, &count_command);
				close(fd);
				return (1);
			}
			close(fd);
		}
		else
			count++;
	}
	return(0);
}

void	free_heredoc_names(t_minishell *s_minishell, int *count_command)
{
	free(s_minishell->heredoc_names[(*count_command)]);
	s_minishell->heredoc_names[(*count_command)] = NULL;
	(*count_command)++;
	while(s_minishell->heredoc_names[(*count_command)] != NULL)
	{
		free(s_minishell->heredoc_names[(*count_command)]);
		(*count_command)++;
	}
	free_all(s_minishell->heredoc_names);
}

int	heredoc_process(int	*count, t_minishell *s_minishell,
			int *count_command, int *fd)
{
	char	*limit;
	char	*cmp;

	(*count)++;
	limit = s_minishell->splited_prompt[(*count)];
	free(s_minishell->heredoc_names[(*count_command)]);
	s_minishell->heredoc_names[(*count_command)] = get_heredoc_name();
	if(s_minishell->heredoc_names[(*count_command)] == NULL)
				return(1);
	(*fd) = open(s_minishell->heredoc_names[(*count_command)],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cmp = readline(">");
	while (cmp != NULL && (ft_memcmp(limit, cmp, ft_strlen(limit)) != 0
			|| ft_memcmp(limit, cmp, ft_strlen(cmp)) != 0))
	{
		cmp = malloc_var(cmp, s_minishell->envp);
		write((*fd), cmp, ft_strlen(cmp));
		write((*fd), "\n", 1);
		free(cmp);
		cmp = readline(">");
		if (cmp == NULL)
			break ;
	}
	free(cmp);
	(*count)++;
	if (g_signal == SIGINT)
		return (1);
	return(0);
}
