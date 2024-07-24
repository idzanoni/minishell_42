/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:37:07 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/24 20:00:27 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_export(t_minishell *s_minishell, t_fds fd_redirect)
{
	int			count;
	int			i;

	count = 1;
	s_minishell->exit_status = 0;
	if (s_minishell->current_cmd[1] == NULL)
		export_only(s_minishell, fd_redirect);
	else
	{
		while (s_minishell->current_cmd[count] != NULL)
		{
			i = 1;
			if (ft_isalpha(s_minishell->current_cmd[count][0]) == 1
			|| s_minishell->current_cmd[count][0] == '_')
			{
				if (valid_export_var_name (&count, &i, s_minishell) == 1)
					find_inenvp_export(s_minishell, &count, &i);
			}
			else
				s_minishell->exit_status = print_error(\
					s_minishell->current_cmd[count], \
						": not a valid identifier");
			count++;
		}
	}
}

void	print_different(t_env_list *env, int fd)
{
	int			len;
	char		*all;
	char		*s;

	len = 0;
	s = NULL;
	//  if (!all)
	//  	return
	while (env != NULL)
	{
		len = 0;
		int a;
		a = ft_strlen(env->content);
		all = calloc((a + 17) , sizeof(char));
		// s = malloc(12 * sizeof(char));
		s = "declare -x ";
		a = 0;
		while(s[a] != '\0')
		{
			all[len] = s[a];
			len++;
			a++;
		}
		len = 12;
		a = 0;
		// free(s);
		s = ft_strchr(env->content, '=');
		if(s != NULL)
		{
		while(env->content[a] != '=')
		{
			all[len] = env->content[a];
			len++;
			a++;
		}
			a = 0;
				all[len++] = s[a++];
				all[len++] = '"';
			while(s[a] != '\0')
			{
				all[len] = s[a];
				len++;
				a++;
			}
			all[len++] = '"';
		}
		else
		{
			while(env->content[a] != '\0')
			{
				all[len] = env->content[a];
				len++;
				a++;
			}
		}
		all[len++] = '\n';
		all[len] = '\0';
		write(fd, all, len);
		free(all);
		env = env->next;
	}
}

void	export_only(t_minishell *s_minishell, t_fds fd_redirect)
{
	t_env_list	*temp;
	int			index;

	temp = s_minishell->envp;
	print_different(temp, fd_redirect.fd_out);
	return ;
	while (temp != NULL)
	{
		ft_putstr_fd("declare -x ", fd_redirect.fd_out);
		index = 0;
		if (ft_strchr(temp->content, '=') != NULL)
		{
			// while (temp->content[index] != '=')
			// {
			// 	ft_putchar_fd(temp->content[index], fd_redirect.fd_out);
			// 	index++;
			// }
			// ft_putchar_fd(temp->content[index++], fd_redirect.fd_out);
			// ft_putchar_fd('"', fd_redirect.fd_out);
			// ft_putstr_fd(&temp->content[index], fd_redirect.fd_out);
			// ft_putendl_fd("\"", fd_redirect.fd_out);
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
			s_minishell->current_cmd[(*count)]) == 1)
	{
		if (s_minishell->current_cmd[(*count)][(*i)] == '=')
		{
			local = localize_envp(s_minishell->envp,
					s_minishell->current_cmd[(*count)]);
			free(local->content);
			local->content = ft_strdup(s_minishell->current_cmd[(*count)]);
		}
	}
	else
		ft_lstadd_back (&s_minishell->envp,
			ft_lstnew(ft_strdup(s_minishell->current_cmd[(*count)])));
}

int	valid_export_var_name(int *count, int *i, t_minishell *s_minishell)
{
	while (s_minishell->current_cmd[(*count)][(*i)] != '\0'
		&& s_minishell->current_cmd[(*count)][(*i)] != '=')
	{
		if (ft_isalnum((s_minishell->current_cmd)[*count][*i]) == 1
		|| ((s_minishell->current_cmd))[(*count)][(*i)] == '_')
			(*i)++;
		else
		{
			print_error(s_minishell->current_cmd[(*count)],
				": not a valid identifier");
			s_minishell->exit_status = 1;
			return (0);
		}
	}
	return (1);
}
