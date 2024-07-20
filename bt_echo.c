/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:18:17 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/20 19:38:12 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_echo(t_minishell *s_minishell, t_fds fd_redirect)
{
	int	count;
	int	n;
	int	val;

	count = 1;
	n = 0;
	val = 0;
	while (s_minishell->current_command[count] != NULL)
	{
		if (s_minishell->current_command[count][0] == '-')
			echo_n(&n, &count, &val, s_minishell->current_command);
		else
		{
			ft_putstr_fd(s_minishell->current_command[count],
				fd_redirect.fd_out);
			if (s_minishell->current_command[count + 1] != NULL)
				write(fd_redirect.fd_out, " ", 1);
			count++;
			val++;
		}
	}
	if (n == 0)
		write(fd_redirect.fd_out, "\n", 1);
}

void	echo_n(int *n, int *count, int *val,
	char **splited_prompt)
{
	if (splited_prompt[(*count)][1] == 'n' && (*val) == 0)
	{
		(*count)++;
		(*n)++;
	}
	else
	{
		ft_putstr_fd(splited_prompt[(*count)], 1);
		write(1, " ", 1);
		(*count)++;
		(*val)++;
	}
}
