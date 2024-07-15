/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:06:53 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/15 15:34:28 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ignore_quotes(int *count, char *prompt)
{
	char	quote;

	quote = prompt[(*count)];
	(*count)++;
	while (prompt[(*count)] != quote)
		(*count)++;
	(*count)++;
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

void	new_prompt(char *prompt)
{
	int		count;
	char	quote;

	count = 0;
	while (prompt[count] != '\0')
	{
		if (prompt[count] == '"' || prompt[count] == '\'')
		{
			quote = prompt[count++];
			while (prompt[count] != quote)
				count++;
			count++;
		}
		else
		{
			while (prompt[count] != ' ' && prompt[count] != '\0'
				&& prompt[count] != '	')
				count++;
			if (prompt[count] == ' ' || prompt[count] == '	')
			{
				prompt[count] = -42;
				count++;
			}
		}
	}
}
