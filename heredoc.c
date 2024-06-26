/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:27:02 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/06/25 19:15:40 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(char	**prompt)
{
	char	*limit;
	int		count;
	char	*cmp;
	int		fd;
	
	count = 0;
	
	while (prompt[count] != NULL)
	{
		if (prompt[count][0] == '<' && prompt[count][1] == '<')
		{
			if(prompt[count] == NULL)
				break;
			count++;
			limit = prompt[count];
			fd = open("arquivo", O_RDWR | O_CREAT, 0644);
			cmp = readline(">");
			while (ft_memcmp(limit, cmp, ft_strlen(limit)) != 0)
			{
				cmp = readline(">");
				write(fd, cmp, ft_strlen(cmp));
				write(fd, "\n", 1);
			}
			count++;
		}
		else
			count++;
	}
	
}