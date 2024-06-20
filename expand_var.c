/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:21:15 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/06/20 20:10:08 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*TO DO
strlen da linha completa -
strlen do nome da variavel $var +
strlen do valor da variavel

mallocar novo tamanho
copiar caracter por caracter até $(andar até o espaço)
copiar valor da $var
voltar pra pra pegar o resto da string
*/

void expand_var(char **splited_prompt, t_env_list *envp)
{
	int	count;

	count = 0;
	printf("estou no inicio\n");
	while(splited_prompt[count] != NULL)
	{
		printf("entrei no while\n");
		mod_quots(splited_prompt[count]);
		splited_prompt[count] = malloc_var(splited_prompt[count], envp);
		remov_quots(splited_prompt[count]);
		count++;
		printf("rodei no while\n");
	}
}

void	mod_quots(char *input)
{
	int	i;

	i = 0;
		while(input[i] != '\0')
		{
			if(input[i] == '"')
			{
				input[i] = -42;
				i++;
				while(input[i] != '"' && input[i] != '\0')
					i++;
				input[i] = -42;
				i++;
			}
			else if(input[i] == '\'')
			{
				input[i] = -24;
				i++;
				while(input[i] != '\'' && input[i] != '\0')
					i++;
				input[i] = -24;
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
		if(input[i] == -24)
		{
			ft_memmove(&input[i], &input[i + 1], ft_strlen(&input[i]));
			while(input[i] != -24)
				i++;
			ft_memmove(&input[i], &input[i + 1], ft_strlen(&input[i]));
		}
		else if(input[i] == -42)
		{
			ft_memmove(&input[i], &input[i + 1], ft_strlen(&input[i]));
			while(input[i] != -42)
				i++;
			ft_memmove(&input[i], &input[i + 1], ft_strlen(&input[i]));
		}
		else
			i++;
	}
}

char *malloc_var(char	*input, t_env_list	*envp)
{
	int	len;
	int	var_len;
	int	i;
	char	*result;
	char 	*substr;
	int j;

	i = 0;
	j = 0;
	len = ft_strlen(input);
	while(input[i] != '\0')
	{
		if(input[i] == -24)
		{
			i++;
			while (input[i] != -24)
				i++;
			i++;
		}
		
		if(input[i] == '$' && (ft_isalpha(input[i + 1]) == 1 || input[i + 1] == '_'))
		{
			i++;
			if(ft_isalpha(input[i]) == 1 || input[i] == '_')
			{
				var_len = i;
				while(ft_isalnum(input[var_len] != 1 && input[var_len] != '_' && input[var_len] != '\0'))
				{
					var_len++;
				}
				substr= ft_substr(input, i, var_len - i + 1);
				if (substr == NULL)
					return(NULL);
				i = var_len;
				len = len - ft_strlen(substr);
				len = len + ft_strlen(return_value(envp, substr));
			}
		}
		else
			i++;
			
	}
	result = calloc(len + 1, sizeof(char));
	if(result == NULL)
		return(NULL);
	i = 0;

	while(input[i] != '\0')
	{
		
		if(input[i] == '$' && (ft_isalpha(input[i + 1]) == 1 || input[i + 1] == '_'))
		{
			i++;
			var_len = i;
			while(ft_isalnum(input[var_len] != 1 && input[var_len] != '_' && input[var_len] != '\0'))
			{
				var_len++;
			}
			substr = ft_substr(input, i, var_len - i + 1);
			substr = return_value(envp, substr);
			i = var_len;
			var_len = 0;
			while(substr[var_len] != '\0')
			{
				result[j] = substr[var_len];
				j++;
				j++;
			}
		}
		else
		{
			result[j] = input[i];
			j++;
			i++;
		}

	}
	return(result);
}

