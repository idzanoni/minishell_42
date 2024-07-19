/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:06:53 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/19 19:07:52 by mgonzaga         ###   ########.fr       */
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

int	check_builtin(char *splited_prompt)
{
	if (!ft_memcmp(splited_prompt, EXIT, ft_strlen(EXIT)))
		return (1);
	if (!ft_memcmp(splited_prompt, ENV, ft_strlen(ENV)))
		return (2);
	if (!ft_memcmp(splited_prompt, ECHO, ft_strlen(ECHO)))
		return (3);
	if (!ft_memcmp(splited_prompt, PWD, ft_strlen(PWD)))
		return (4);
	if (!ft_memcmp(splited_prompt, CD, ft_strlen(CD)))
		return (5);
	if (!ft_memcmp(splited_prompt, EXPORT, ft_strlen(EXPORT)))
		return (6);
	if (!ft_memcmp(splited_prompt, UNSET, ft_strlen(UNSET)))
		return (7);
	else
		return (0);
}

void	copy_quotes(int *count, char *prompt, int *len, char *result)
{
	char	quote;

	quote = prompt[(*count)];
	result[(*len)] = prompt[(*count)];
	(*count)++;
	(*len)++;
	while (prompt[(*count)] != quote)
	{
		result[(*len)] = prompt[(*count)];
		(*count)++;
		(*len)++;
	}
	result[(*len)] = prompt[(*count)];
	(*count)++;
	(*len)++;
}
