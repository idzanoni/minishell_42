/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:21:15 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/06/19 20:03:00 by mgonzaga         ###   ########.fr       */
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

char **expand_var(char **splited_prompt, char **envp)
{
	int	count;

	count = 0;
	while(splited_prompt[count] != NULL)
	{
		splited_prompt[count] = really_expand(splited_prompt[count], envp);
		count++;
	}
}


char	*really_expand(char *splited_prompt, char	**envp)
{
	int	count;
	int i;
	count = 0;
	while(splited_prompt[count] != '\0')
	{
		if(splited_prompt[0] == '$')
		{
			splited_prompt = malloc_var(splited_prompt, envp)
		}
	}
}

char *malloc_var(char	*input, t_list	*envp)
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
		if(input[i] == '\'')
		{
			i++;
			while (input[i] != '\'')
				i++;
			i++;
		}
		
		if(input[i] == '$' && input[i + 1] != ' ')
		{
			if(ft_isalpha(input[i]) == 1 || input[i] == '_')
			{
				var_len = i;
				while(ft_isalnum(input[var_len] != 1 && input[var_len] != '_' && input[var_len] != '\0'))
				{
					var_len++;
				}
				substr= ft_substr(input, i, var_len - i + 1);
				if (substr == NULL)
				{}
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
		return();
	i = 0;

	while(input[i] != '\0')
	{

		if(input[i] != '$')
		{
			result[j] = input[i];
			j++;
			i++;
		}
		else
		{
			if(ft_isdigit(input[i + 1]) ==)
		}

	}

}

