/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:18:17 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/24 21:58:03 by mgonzaga         ###   ########.fr       */
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
	s_minishell->exit_status = 0;
	while (s_minishell->current_cmd[count] != NULL)
	{
		if (s_minishell->current_cmd[count][0] == '-')
		{			
			if(echo_n(&n, &count, &val, s_minishell->current_cmd) == 1)
			{
				 	ft_putstr_fd(s_minishell->current_cmd[count - 1], fd_redirect.fd_out);
					if(s_minishell->current_cmd[count] != NULL)
						ft_putstr_fd(" ", fd_redirect.fd_out);
			}
		}
		else
		{
			ft_putstr_fd(s_minishell->current_cmd[count],
				fd_redirect.fd_out);
			if (s_minishell->current_cmd[count + 1] != NULL)
				write(fd_redirect.fd_out, " ", 1);
			count++;
			val++;
		}
	}
	if (n == 0)
		write(fd_redirect.fd_out, "\n", 1);
}

int	echo_n(int *n, int *count, int *val,
	char **splited_prompt)
{
	int	i;

	i = 1;
	if (splited_prompt[(*count)][1] == 'n' && (*val) == 0)
	{
		while(splited_prompt[(*count)][i] != '\0')
		{
			if(splited_prompt[(*count)][i] != 'n')
			{
				(*count)++;
				return(1);
			}
			i++;
		}
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
	return(0);
}
