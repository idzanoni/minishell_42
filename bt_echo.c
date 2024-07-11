/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:18:17 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/11 17:09:22 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_echo(t_minishell *s_minishell)
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
			ft_putstr_fd(s_minishell->current_command[count], 1);
			write(1, " ", 1);
			count++;
			val++;
		}
	}
	if (n == 0)
		write(1, "\n", 1);
}

void	echo_n(int *n, int *count, int *val, char **splited_prompt)
{
	if (splited_prompt[(*count)][1] == 'n' && (*val) == 0)
	{
		(*count)++;
		(*n)++;
	}
	else
	{
		ft_putstr_fd(splited_prompt[(*count)], 1);
		(*count)++;
		(*val)++;
	}
}
