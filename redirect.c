/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:38:22 by izanoni           #+#    #+#             */
/*   Updated: 2024/06/19 18:38:48 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirect(char **splited_prompt)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while(splited_prompt[count] != NULL)
	{
		if(splited_prompt[count][0] == '<' || splited_prompt[count][0] == '>')
		{
			free(splited_prompt[count]);
			count++;
			free(splited_prompt[count]);
			i = count;
			while (splited_prompt[i] != NULL)
			{
				splited_prompt[i - 1] = splited_prompt[i + 1];
				i++;
			}		
			count = count - 2;
		}
		count++;
	}
}

t_fds find_redirect(char **splited_prompt)
{
	t_fds fd_redirect;
	int count;

	fd_redirect.fd_in = STDIN_FILENO;
	fd_redirect.fd_out = STDOUT_FILENO;
	count = 0;
	while (splited_prompt[count] != NULL)
	{
		if (splited_prompt[count][0] == '>')
		{
			if (fd_redirect.fd_out != STDOUT_FILENO)
				close (fd_redirect.fd_out);
			if (splited_prompt[count][1] == '>')
				fd_redirect.fd_out = open (splited_prompt[count + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				fd_redirect.fd_out = open (splited_prompt[count + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		else if (splited_prompt[count][0] == '<')
		{
			if (fd_redirect.fd_in != STDIN_FILENO)
				close (fd_redirect.fd_in);
			if (splited_prompt[count][1] == '<')
			{}
			else
				fd_redirect.fd_in = open (splited_prompt[count + 1], O_RDONLY);
		}
		count++;
	}
	return(fd_redirect);
}
