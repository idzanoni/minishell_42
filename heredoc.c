/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:27:02 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/06/24 18:17:07 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(char	**prompt)
{
	char	*limit;
	int		count;
	char	*cmp;
	
	count = 0;
	while(prompt[count] != NULL)
	{
		if(prompt[count][0] == '<' && prompt[count][1] == '<')
		{
			if(prompt[count] == NULL)
				break;
			count++;
			limit = prompt[count];
			open("arquivo", O_WRONLY | O_CREAT, 0644);
			cmp = readline(">");
			while(ft_memcmp(limit, cmp, ft_strlen(limit)) != 0)
			{
				cmp = readline(">");
			}
			printf("%s", prompt[count]);
			count++;
		}
		else
			count++;
		if(prompt[count] == NULL)
			break;
		printf(" final do while %s\n", prompt[count]);
	}
}