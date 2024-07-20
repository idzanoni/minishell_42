/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:21:15 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/20 19:47:56 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_matrix(char **splited_prompt, int start)
{
	int	temp_count;

	temp_count = start;
	while (splited_prompt[temp_count] != NULL)
	{
		splited_prompt[temp_count] = splited_prompt[temp_count + 1];
		temp_count++;
	}
}

void	expand_var(char **splited_prompt, t_env_list *envp, t_minishell *s_minishell)
{
	int	count;

	count = 0;
	while (splited_prompt[count] != NULL)
	{
		mod_quots(splited_prompt[count]);
		splited_prompt[count] = malloc_var(splited_prompt[count], envp, s_minishell);
		if (splited_prompt[count][0] == '\0')
		{
			free(splited_prompt[count]);
			move_matrix(splited_prompt, count);
		}	
		remov_quots(splited_prompt[count]);
		count++;
	}
}

void	mod_quots(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '"')
		{
			input[i] = -41;
			i++;
			while (input[i] != '"' && input[i] != '\0')
				i++;
			input[i++] = -41;
		}
		else if (input[i] == '\'')
		{
			input[i] = -21;
			i++;
			while (input[i] != '\'' && input[i] != '\0')
				i++;
			input[i] = -21;
			i++;
		}
		else
			i++;
	}
}

void	remov_quots(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == -21)
		{
			ft_memmove(&input[i], &input[i + 1], ft_strlen(&input[i]));
			while (input[i] != -21 && input[i] != '\0')
				i++;
			ft_memmove(&input[i], &input[i + 1], ft_strlen(&input[i]));
		}
		else if (input[i] == -41)
		{
			ft_memmove(&input[i], &input[i + 1], ft_strlen(&input[i]));
			while (input[i] != -41 && input[i] != '\0')
				i++;
			ft_memmove(&input[i], &input[i + 1], ft_strlen(&input[i]));
		}
		else
			i++;
	}
}

int	malloc_len(char	*input, t_env_list	*envp, t_minishell *s_minishell)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(input);
	while (input[i] != '\0')
	{
		if (input[i] == -21)
		{
			i++;
			while (input[i] != -21 && input[i] != '\0')
				i++;
			i++;
		}
		else if (input[i] == '$' && (ft_isalpha(input[i + 1]) == 1
				|| input[i + 1] == '_'))
		{
			i++;
			if (ft_isalpha(input[i]) == 1 || input[i] == '_')
				malloc_len_process(input, &len, &i, envp);
		}
		else if (input[i] == '$' && input[i + 1] == '?')
		{
			len = len - 2 + count_digits(s_minishell->exit_status);
			i = i + 2;
		}
		else
			i++;
	}
	return (len);
}

int count_digits(int i)
{
	int count;

	count = 1;
	while (i >= 10)
	{
		i = i / 10;
		count++;
	}
	return(count);
}