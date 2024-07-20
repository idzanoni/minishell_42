/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:16:05 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/20 16:51:22 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bt_env(t_minishell *s_minishell, t_fds fd_redirect)
{
	int			i;
	t_env_list	*envp;

	envp = s_minishell->envp;
	s_minishell->exit_status = 0;
	while (envp != NULL)
	{
		i = 0;
		while (((char *)(envp->content))[i] != '\0')
		{
			if (((char *)envp->content)[i] == '=')
			{
				ft_putstr_fd(((char *)envp->content), fd_redirect.fd_out);
				write(fd_redirect.fd_out, "\n", 1);
				break ;
			}
			i++;
		}		
		envp = envp->next;
	}
	return (0);
}
