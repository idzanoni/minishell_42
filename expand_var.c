/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:21:15 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/01 19:44:48 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    move_matrix(char **splited_prompt, int start)
{
	int    temp_count;
	
	temp_count = start;
	while(splited_prompt[temp_count] != NULL)
	{
		splited_prompt[temp_count] = splited_prompt[temp_count + 1];
		temp_count++;
	}
}

void expand_var(char **splited_prompt, t_env_list *envp)
{
	int    count;

	count = 0;
	while(splited_prompt[count] != NULL)
	{
		mod_quots(splited_prompt[count]);
		splited_prompt[count] = malloc_var(splited_prompt[count], envp);
		if (splited_prompt[count][0] == '\0')
		{
			free(splited_prompt[count]);
			move_matrix(splited_prompt, count);
		}
		remov_quots(splited_prompt[count]);
		count++;
	}
}
//"sada""$HOME"'$HOME"'"home'"
void	mod_quots(char *input)
{
	int	i;

	i = 0;
		while(input[i] != '\0')
		{
			if(input[i] == '"')
			{
				input[i] = -41;
				i++;
				while(input[i] != '"' && input[i] != '\0')
					i++;
				input[i] = -41;
				i++;
			}
			else if(input[i] == '\'')
			{
				input[i] = -21;
				i++;
				while(input[i] != '\'' && input[i] != '\0')
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
	while(input[i] != '\0')
	{
		if(input[i] == -21)
		{
			ft_memmove(&input[i], &input[i + 1], ft_strlen(&input[i]));
			while(input[i] != -21 && input[i] != '\0')
				i++;
			ft_memmove(&input[i], &input[i + 1], ft_strlen(&input[i]));
		}
		else if(input[i] == -41)
		{
			ft_memmove(&input[i], &input[i + 1], ft_strlen(&input[i]));
			while(input[i] != -41 && input[i] != '\0')
				i++;
			ft_memmove(&input[i], &input[i + 1], ft_strlen(&input[i]));
		}
		else
			i++;
	}
}

int malloc_len(char	*input, t_env_list	*envp)
{
	int	len;
	int	var_len;
	int	i;
	char 	*substr;
	
	i = 0;
	len = ft_strlen(input);
	var_len = 0;
	while(input[i] != '\0')
	{
		if(input[i] == -21)
		{
			i++;
			while (input[i] != -21 && input[i] != '\0')
				i++;
			i++;
		}
		else if (input[i] == '$' && (ft_isalpha(input[i + 1]) == 1 || input[i + 1] == '_'))
		{
			i++;
			if (ft_isalpha(input[i]) == 1 || input[i] == '_')
			{
				var_len = i;
				while ((ft_isalnum(input[var_len]) == 1 || input[var_len] == '_') && input[var_len] != '\0')
				{
					var_len++;
				}
				substr = ft_substr(input, i, var_len - i);
				if (substr == NULL)
					return(0);
				i = var_len;
				len = len - ft_strlen(substr);
				len = len + ft_strlen(return_value(envp, substr));
				free(substr);
			}
		}
		else
			i++;
	}
	return (len);
}

char	*malloc_var (char *input, t_env_list	*envp)
{
	char	*result;
	char	*substr;
	int		i;
	int		len;
	int		var_len;

	i = 0;
	len = malloc_len(input, envp);
	result = calloc(len + 1, sizeof(char));
	len = 0;
	while (input[i] != '\0')
	{
		if (input[i] == -21)
		{
			i++;
			while (input[i] != -21 && input[i] != '\0')
			{
				result[len] = input[i];
				len++;
				i++;
			}
			i++;
		}
		else if (input[i] == '$' && (ft_isalpha(input[i + 1]) == 1
				|| input[i + 1] == '_'))
		{
			i++;
			var_len = i;
			while ((ft_isalnum(input[var_len]) == 1 || input[var_len] == '_')
						&& input[var_len] != '\0')
				var_len++;
			substr = ft_substr(input, i, var_len - i);
			i = var_len;
			if (valid_var(envp, substr) == 1)
			{
				substr = return_value(envp, substr);
				var_len = 0;
				while (substr[var_len] != '\0')
				{
					result[len] = substr[var_len];
					len++;
					var_len++;
				}
			}
		}
		else
		{
			result[len] = input[i];
			len++;
			i++;
		}
	}
	result[len] = '\0';
	free(input);
	return (result);
}
