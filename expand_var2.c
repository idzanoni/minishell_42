/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:13:15 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/20 19:54:31 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_len_process(char	*input, int *len, int *i, t_env_list *envp)
{
	char	*substr;
	int		var_len;

	var_len = (*i);
	while ((ft_isalnum(input[var_len]) == 1 || input[var_len] == '_')
		&& input[var_len] != '\0')
		var_len++;
	substr = ft_substr(input, (*i), var_len - (*i));
	if (substr == NULL)
		(*len) = 0;
	else
	{
		i = &var_len;
		(*len) = (*len) - ft_strlen(substr);
		(*len) = (*len) + ft_strlen(return_value(envp, substr));
	}
	free(substr);
}

char	*malloc_var(char *input, t_env_list	*envp, t_minishell *s_minishell)
{
	char	*result;
	int		i;
	int		len;
	char	*substr;
	char	*str_exit_status;

	i = 0;
	len = malloc_len(input, envp, s_minishell);
	result = calloc(len + 1, sizeof(char));
	len = 0;
	while (input[i] != '\0')
	{
		if (input[i] == -21)
			walk_simple_quote(&i, input, result, &len);
		else if (input[i] == '$' && input[i + 1] == '?')
		{
			str_exit_status = ft_itoa(s_minishell->exit_status);
			if (str_exit_status == NULL)
			{}
			ft_strlcpy(result + len, str_exit_status, ft_strlen(str_exit_status) + 1);
			len = len + ft_strlen(str_exit_status);
			i = i + 2;
			free(str_exit_status);
		}
		else if (input[i] == '$' && (ft_isalpha(input[i + 1]) == 1 || input[i + 1] == '_'))
		{
			substr = put_substr(&i, input);
			put_result(substr, &len, envp, result);
			free(substr);
		}
		else
			result[len++] = input[i++];
	}
	result[len] = '\0';
	free(input);
	return (result);
}

void	walk_simple_quote(int *i, char *input, char *result, int *len)
{
	result[(*len)] = input[(*i)];
	(*i)++;
	(*len)++;
	while (input[(*i)] != -21 && input[(*i)] != '\0')
	{
		result[(*len)] = input[(*i)];
		(*len)++;
		(*i)++;
	}
	result[(*len)] = input[(*i)];
	(*len)++;
	(*i)++;
}

void	put_result(char *substr, int *len, t_env_list *envp, char *result)
{
	int		var_len;

	if (valid_var(envp, substr) == 1)
	{
		substr = return_value(envp, substr);
		var_len = 0;
		while (substr[var_len] != '\0')
		{
			result[(*len)] = substr[var_len];
			(*len)++;
			var_len++;
		}
	}
}

char	*put_substr(int *i, char *input)
{
	int		var_len;
	char	*substr;

	(*i)++;
	var_len = (*i);
	while ((ft_isalnum(input[var_len]) == 1 || input[var_len] == '_')
		&& input[var_len] != '\0')
		var_len++;
	substr = ft_substr(input, (*i), var_len - (*i));
	(*i) = var_len;
	return (substr);
}
