/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:16:05 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/24 16:32:42 by izanoni          ###   ########.fr       */
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

void	print_different_env(t_env_list *env, int fd)
{
	int			len;
	char		*all;
	t_env_list	*temp;

	temp = env;
	len = 0;
	while (temp != NULL)
	{
		len += ft_strlen(temp->content) + 1;
		temp = temp->next;
	}
	all = malloc((len + 1) * sizeof(char));
	//  if (!all)
	//  	return
	len = 0;
	while (env != NULL)
	{
		len += ft_strlcpy(all + len, env->content, ft_strlen(env->content) + 1);
		all[len++] = '\n';
		all[len] = '\0';
		env = env->next;
	}
	write(fd, all, len);
	free(all);
}
