/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:59:21 by izanoni           #+#    #+#             */
/*   Updated: 2024/06/17 19:48:59 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Variável tem nome válido igual as variáveis no C
	- Só pode conter letras, números e _
	- Não pode começar com números
*/
char	*bt_unset(char **splited_prompt, t_list	**envp)
{
	int		i;
	int		len_var;
	t_list	*temp_node;

	i = 1;
	while (splited_prompt[i] != NULL)
	{
		if (checkname(splited_prompt[i]) != 0)
		{
			print_error(splited_prompt[i], ": not a valid identifier\n");
			i++;
			continue;
		}
		len_var = ft_strlen(splited_prompt[i]);
		temp_node = *envp;
		while (temp_node != NULL)
		{
			if ((ft_strnstr(temp_node->content, splited_prompt[i], len_var)) != NULL)
			{
				if ((temp_node->content)[len_var] == '=' || (temp_node->content)[len_var] == '\0')
				{
					delnode(envp, temp_node);
					break ;
				}
			}
			temp_node = temp_node->next;
		}
		i++;
	}
}

void	delnode(t_list	**envp, t_list	*node)
{
	t_list *temp;

	temp = *envp;
	if (node == *envp)
	{
		(*envp) = (*envp)->next;
		free (node->content);
		free (node);
	}
	else
	{
		while (temp != NULL && temp->next != node)
			temp = temp->next;
		if (temp == NULL)
			return ;
		else
		{
			temp->next = node->next;
			free (node->content);
			free (node);
		}
	}
}

/* Exemplos
""
@kkkkkk
V@R
teste
ap4en45_um4_var
_serassi?
73573
7este
4vari@vel_v@lid@
*/
int checkname(char *splited_prompt)
{
	int i;
	
	i = 0;
	if (ft_isdigit (splited_prompt[i]) == 1)
		return (1);
	while (splited_prompt[i] != '\0')
	{
		if (ft_isalnum(splited_prompt[i]) != 1 && splited_prompt[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

//'var' message
void	print_error(char *var, char *message)
{
	int len;
	int count;
	char *temp;

	count = 0;
	len = ft_strlen(var) + ft_strlen(message) + 2;
	temp = malloc((len+2) * sizeof(char));
	if (!temp)
		return;
	len = 0;
	temp[count] = '\'';
	while (var[len] != '\0')
	{
		count++;
		temp[count] = var[len];
		len++;
	}
	temp[count++] = '\'';
	len = 0;
	while(message[len] != '\0')
	{
		temp[count] = message[len];
		count++;
		len++;
	}
	temp[count] = '\n';
	temp[++count] = '\0';
	write(2,temp,ft_strlen(temp));
	free(temp);
}
