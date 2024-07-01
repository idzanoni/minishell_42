/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:39:06 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/01 19:40:02 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(char **malloc_string)
{
	int	count;

	count = 0;
	if (!malloc_string)
		return ;
	while (malloc_string[count] != NULL)
	{
		free(malloc_string[count]);
		count++;
	}
	free(malloc_string);
}

void	free_list(t_env_list *envp)
{
	t_env_list	*current_node;
	t_env_list	*next_node;

	current_node = envp;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node->content);
		free(current_node);
		current_node = next_node;
	}
}
