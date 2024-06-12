/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:59:21 by izanoni           #+#    #+#             */
/*   Updated: 2024/06/12 19:23:05 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*bt_unset(char **splited_prompt, t_list	**envp)
{
	int		i;
	int		len_var;
	t_list	*temp_node;

	i = 1;
	while (splited_prompt[i] != NULL)
	{
		len_var = ft_strlen(splited_prompt[i]);
		temp_node = *envp;
		while(temp_node != NULL)
		{
			if((ft_strnstr((char *)temp_node->content, splited_prompt[i], len_var)) != NULL)
			{
				if (((char *)temp_node->content)[len_var] == '=' || ((char *)temp_node->content)[len_var] == '\0')
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
