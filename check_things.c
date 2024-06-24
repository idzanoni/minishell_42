/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:12:45 by izanoni           #+#    #+#             */
/*   Updated: 2024/06/24 14:12:51 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipes(char *prompt)
{
	int 	count;
	char	quote;

	count = 0;
	while (prompt[count] == ' ' || prompt[count] == '	')
		count++;
	if (prompt[count] == '|')
		return (-1);
	while(prompt[count] != '\0')
	{
		if (prompt[count] == 34 || prompt[count] == 39)
		{
			quote = prompt[count];
			while (prompt[count] != quote)
				count ++;
		}
		if (prompt[count] == '|')
		{
			count++;
			while (prompt[count] == ' ' || prompt[count] == '	')
				count++;
			if (prompt[count] == '\0' || prompt[count] == '|')
				return (-1);
		}
		else
			count++;
	}
	return (0);
}

int	check_quotes(char *prompt)
{
	int i;
	int quotes;
	int	checker;
	
	checker = 0;
	i = -1;
	while (prompt[++i] != '\0')
	{
		if (prompt[i] == 34 || prompt[i] == 39)
		{
			quotes = prompt[i];
			if (prompt[i] == 34)
				while (prompt[++i] != 34 && prompt[i] != '\0')
					;
			else if (prompt[i] == 39)
				while (prompt[++i] != 39 && prompt[i] != '\0')
					;
			if (prompt[i] != quotes)
				checker = -1;
		}
		if (prompt[i] == '\0')
			break ;
	}
	return (checker);
}

int	check_redirect(char *prompt)
{
	int		count;
	char	quote;

	count = 0;
	while(prompt[count] != '\0')
	{
		if (prompt[count] == 34 || prompt[count] == 39)
		{
			quote = prompt[count];
			while (prompt[count] != quote)
				count ++;
		}
		if(prompt[count] == '>' || prompt[count] == '<')
		{
			count++;
			if ((prompt[count] != prompt[count - 1]) && (prompt[count] == '>' || prompt[count] == '<'))
				return(-1);
			else if (prompt[count] == '>' || prompt[count] == '<')
				count++;
			while (prompt[count] == ' ' || prompt[count] == '\t')
				count++;
			if(prompt[count] == '\0' || prompt[count] == '|' 
				|| prompt[count] == '>' || prompt[count] == '<')
			{
				printf("error redirect\n");
				return(-1);
			}
		}
		count++;
	}
	return(0);
}

int	only_space(char *prompt)
{
	int count;

	count = 0;
	while (prompt[count] != '\0')
	{
		if (prompt[count] != ' ' && prompt[count] != '\t') 
			return(0);
		count++;
	}
	return (-1);
}  

int	check_empty(char *prompt)
{
	if (prompt[0] == '\0')
		return (-1);
	else
		return (0);
}

int	check_prompt(char *prompt)
{
	if (check_empty(prompt))
		return (-1);
	add_history(prompt);
	if (only_space(prompt))
		return (-1);
	if (check_quotes(prompt))
		return (-1);
	if (check_redirect(prompt))
		return (-1);
	if (check_pipes(prompt))
		return (-1);
	return (0);
}
