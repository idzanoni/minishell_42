/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:27:02 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/06/26 19:30:16 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(char	**prompt)
{
	char	*limit;
	int		count;
	char	*cmp;
	int		fd;
	int 	*malloc_vetor;
	int		count_command;

	count = pipes_count(prompt);
	count_command = 0;
	malloc_vetor = malloc((count + 1) * sizeof(int));
	count = 0;
	while (prompt[count] != NULL)
	{
		if (prompt[count][0] == '|')
			count_command++;
		if (prompt[count][0] == '<' && prompt[count][1] == '<')
		{
			if(prompt[count] == NULL)
				break;
			count++;
			limit = prompt[count];
			fd = open("arquivo", O_WRONLY | O_CREAT, 0644);
			malloc_vetor[count_command] = fd;
			cmp = readline(">");
			while (ft_memcmp(limit, cmp, ft_strlen(limit)) != 0)
			{
				cmp = readline(">");
				write(fd, cmp, ft_strlen(cmp));
				write(fd, "\n", 1);
			}
			close(fd);
			count++;
		}
		else
		{
			malloc_vetor[count_command] = -7;
			count++;
			
		}
	}
	count = 0;
	while(count <= count_command)
	{
		printf("%i\n",malloc_vetor[count]);
		count++;
	}
}



int pipes_count(char **prompt)
{
	int count;
	int count_pipes;

	count = 0;
	count_pipes = 0;
	while(prompt[count] != NULL)
	{
		if(prompt[count][0] == '|')
			count_pipes++;
		count++;
	}
	return(count_pipes);
}