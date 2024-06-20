/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:16:05 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/06/20 17:26:00 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bt_env(t_env_list *envp)
{
	int i;

	while(envp != NULL)
	{
		i = 0;
		while(((char *)envp->content)[i] != '\0')
		{
			if (((char *)envp->content)[i] == '=')
			{
				ft_putstr_fd((char *)envp->content, 1);
				break;
			}
			i++;
		}
		envp = envp->next;
	}
	return (0);
}
