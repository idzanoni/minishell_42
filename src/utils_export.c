/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:30:28 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/25 15:32:41 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	while_export(char	*all, int *len, int *a, char *string)
{
	while (string[(*a)] != '\0')
	{
		all[(*len)] = string[(*a)];
		(*len)++;
		(*a)++;
	}
}

void	util_export(t_env_list *env, int *a, int *len, char *all)
{
	char	*s;

	s = ft_strchr(env->content, '=');
	while (env->content[(*a)] != '=')
	{
		all[(*len)] = env->content[(*a)];
		(*len)++;
		(*a)++;
	}
		(*a) = 0;
			all[(*len)++] = s[(*a)++];
			all[(*len)++] = '"';
	while (s[(*a)] != '\0')
	{
		all[(*len)] = s[(*a)];
		(*len)++;
		(*a)++;
	}
	all[(*len)++] = '"';
}

void	export_only(t_minishell *s_minishell, t_fds fd_redirect)
{
	t_env_list	*temp;

	temp = s_minishell->envp;
	print_different(temp, fd_redirect.fd_out);
	return ;
}

void	heredoc_update(t_minishell *s_minishell)
{
	if (s_minishell->heredoc_names != NULL)
	{
		s_minishell->current_heredoc = s_minishell->heredoc_names[0];
		move_matrix(s_minishell->heredoc_names, 0);
	}
}
