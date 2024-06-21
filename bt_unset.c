/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:59:21 by izanoni           #+#    #+#             */
/*   Updated: 2024/06/21 19:09:26 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Variável tem nome válido igual as variáveis no C
	- Só pode conter letras, números e _
	- Não pode começar com números
*/
int	bt_unset(char **splited_prompt, t_env_list	**envp)
{
	int			i;
	int			len_var;
	t_env_list	*temp_node;

	i = 1;
	while (splited_prompt[i] != NULL)
	{
		if (check_name(splited_prompt[i]) != 0)
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
	return(0);
}

void	delnode(t_env_list	**envp, t_env_list	*node)
{
	t_env_list *temp;

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
int check_name(char *splited_prompt)
{
	int i;
	
	i = 0;
	if (ft_isdigit(splited_prompt[i]) == 1)
		return (1);
	while (splited_prompt[i] != '\0')
	{
		if (ft_isalnum(splited_prompt[i]) != 1 && splited_prompt[i] != '_')
			return (1);
		i++;
	}
	return (0);
}


