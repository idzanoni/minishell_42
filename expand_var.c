/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:21:15 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/06/17 19:44:14 by mgonzaga         ###   ########.fr       */
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
			i = ft_strlen(splited_prompt);
			
			
		}
	}
}

char	*malloc_var()

