/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:03:09 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/01 17:51:23 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*norme_string (char *prompt)
{
	int		count;
	char	*result;
	int		size_prompt;
	int		count_result;

	count = 0;
	count_result = 0;
	size_prompt = ft_strlen(prompt);
	while (prompt[count] != '\0')
	{
		if(prompt[count] == '>'|| prompt[count] == '<'
					|| prompt[count] == '|')
			size_prompt = size_prompt + 2;
		count++;
	}
	result = malloc((size_prompt + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	count = 0;
	while (prompt[count] != '\0')
	{
		if (prompt[count] == '>'|| prompt[count] == '<'
		|| prompt[count] == '|')
		{
			result[count_result] = ' ';
			count_result++;
			result[count_result] = prompt[count];
			if (prompt[count + 1] == '>' || prompt[count + 1] == '<')
			{
				count++;
				count_result++;
				result[count_result] = prompt[count];
				count_result++;
				result[count_result] = ' ';
				count++;
				count_result++;
			}
			else
			{
				count_result++;
				result[count_result] = ' ';
				count_result++;
				count++;
			}
		}
		else
		{
			result[count_result] = prompt[count];
			count++;
			count_result++;
		}
	}
	result[count_result] = '\0';
	return (result);
}
