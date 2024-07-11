/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:37:07 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/11 19:34:15 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_export(t_minishell	*s_minishell)
{
	int			count;
	int			i;
	t_env_list	*local;

	count = 1;
	i = 1;
	local = NULL;
	if (s_minishell->splited_prompt[1] == NULL)
		export_only(s_minishell);
	else
	{
		while (s_minishell->splited_prompt[count] != NULL)
		{
			if (ft_isalpha(s_minishell->splited_prompt[count][0]) == 1
			|| s_minishell->splited_prompt[count][0] == '_')
			{
				valid_export_var_name (&count, &i, s_minishell->splited_prompt);
				find_inenvp_export(local, s_minishell, &count, &i);
			}
			else
				ft_putstr_fd ("export:not a valid identifier", 1);
			count++;
		}
	}
}

void	export_only(t_minishell *s_minishell)
{
	while (s_minishell->envp != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(s_minishell->envp->content, 1);
		s_minishell->envp = s_minishell->envp->next;
	}
}

void	find_inenvp_export(t_env_list *local, t_minishell *s_minishell,
				int *count, int	*i)
{
	if (valid_var(s_minishell->envp,
			s_minishell->splited_prompt[(*count)]) == 1)
	{
		if (s_minishell->splited_prompt[(*count)][(*i)] == '=')
		{
			local = localize_envp(s_minishell->envp,
					s_minishell->splited_prompt[(*count)]);
			free(local->content);
			local->content = ft_strdup(s_minishell->splited_prompt[(*count)]);
		}
	}
	else
		ft_lstadd_back (&s_minishell->envp,
			ft_lstnew(ft_strdup(s_minishell->splited_prompt[(*count)])));
}

void	valid_export_var_name(int *count, int *i, char **splited_prompt)
{
	while (splited_prompt[(*count)][(*i)] != '\0'
		&& splited_prompt[(*count)][(*i)] != '=')
	{
		if (ft_isalnum((splited_prompt)[*count][*i]) == 1
		|| ((splited_prompt))[(*count)][(*i)] == '_')
			(*i)++;
		else
		{
			ft_putstr_fd("export:not a valid identifier\n", 1);
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
