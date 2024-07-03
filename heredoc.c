/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:10:52 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/03 16:10:33 by izanoni          ###   ########.fr       */
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

char    *get_heredoc_name(void)
{
	static int    heredoc_number;
	char        *string_of_heredoc_number;
	char        *name;

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



void    heredoc(t_minishell *s_minishell)
{
	char    *limit;
	char    *cmp;
	int        count;
	int        fd;
	int        count_command;

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
			count++;
			limit = s_minishell->splited_prompt[count];
			free(s_minishell->heredoc_names[count_command]);
			s_minishell->heredoc_names[count_command] = get_heredoc_name();
			fd = open(s_minishell->heredoc_names[count_command],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			cmp = readline(">");
			while (cmp != NULL && (ft_memcmp(limit, cmp, ft_strlen(limit)) != 0
						|| ft_memcmp(limit, cmp, ft_strlen(cmp)) != 0))
			{
				cmp = malloc_var(cmp, s_minishell->envp);
				write(fd, cmp, ft_strlen(cmp));
				write(fd, "\n", 1);
				free(cmp);
				cmp = readline(">");
				if (cmp == NULL)
					break ;
			}
			free(cmp);
			close(fd);
			count++;
		}
		else
		{
			count++;
		}
	count = 0;

}
	while(count <= count_command)
	{
		printf("heredoc_name[%i] = %s\n", count, s_minishell->heredoc_names[count]);
		count++;
	}
}

int	pipes_count(char **prompt)
{
	int	count;
	int	count_pipes;

	count = 0;
	count_pipes = 0;
	while (prompt[count] != NULL)
	{
		if (prompt[count][0] == '|')
			count_pipes++;
		count++;
	}
	return (count_pipes);
}
