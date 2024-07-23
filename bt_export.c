/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:37:07 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/23 13:44:58 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_export(t_minishell *s_minishell, t_fds fd_redirect)
{
	int			count;
	int			i;

	count = 1;
	i = 1;
	s_minishell->exit_status = 0;
	if (s_minishell->current_command[1] == NULL)
		export_only(s_minishell, fd_redirect);
	else
	{
		while (s_minishell->current_command[count] != NULL)
		{
			if (ft_isalpha(s_minishell->current_command[count][0]) == 1
			|| s_minishell->current_command[count][0] == '_')
			{
				valid_export_var_name (&count, &i, s_minishell);
				find_inenvp_export(s_minishell, &count, &i);
			}
			else
				s_minishell->exit_status = print_error(\
					s_minishell->current_command[count], \
						": not a valid identifier");
			count++;
		}
	}
}

void	export_only(t_minishell *s_minishell, t_fds fd_redirect)
{
	t_env_list	*temp;
	int			index;

	temp = s_minishell->envp;
	while (temp != NULL)
	{
		ft_putstr_fd("declare -x ", fd_redirect.fd_out);
		index = 0;
		if (ft_strchr(temp->content, '=') != NULL)
		{
			while (temp->content[index] != '=')
			{
				ft_putchar_fd(temp->content[index], fd_redirect.fd_out);
				index++;
			}
			ft_putchar_fd(temp->content[index++], fd_redirect.fd_out);
			ft_putchar_fd('"', fd_redirect.fd_out);
			ft_putstr_fd(&temp->content[index], fd_redirect.fd_out);
			ft_putendl_fd("\"", fd_redirect.fd_out);
		}
		else
			ft_putendl_fd(temp->content, fd_redirect.fd_out);
		temp = temp->next;
	}
}

void	find_inenvp_export(t_minishell *s_minishell, int *count, int *i)
{
	t_env_list	*local;

	if (localize_envp2(s_minishell->envp,
			s_minishell->current_command[(*count)]) == 1)
	{
		if (s_minishell->current_command[(*count)][(*i)] == '=')
		{
			local = localize_envp(s_minishell->envp,
					s_minishell->current_command[(*count)]);
			free(local->content);
			local->content = ft_strdup(s_minishell->current_command[(*count)]);
		}
	}
	else
		ft_lstadd_back (&s_minishell->envp,
			ft_lstnew(ft_strdup(s_minishell->current_command[(*count)])));
}

void	valid_export_var_name(int *count, int *i, t_minishell *s_minishell)
{
	while (s_minishell->current_command[(*count)][(*i)] != '\0'
		&& s_minishell->current_command[(*count)][(*i)] != '=')
	{
		if (ft_isalnum((s_minishell->current_command)[*count][*i]) == 1
		|| ((s_minishell->current_command))[(*count)][(*i)] == '_')
			(*i)++;
		else
		{
			print_error(s_minishell->current_command[(*count)],
				": not a valid identifier");
			s_minishell->exit_status = 1;
			break ;
		}
	}
}

size_t	ft_strlen_2(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '=')
		i++;
	return (i);
}
