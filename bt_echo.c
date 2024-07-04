/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:18:17 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/04 19:43:16 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	bt_echo(char **splited_prompt)
{
	int	count;
	int	n;
	int	val;

	count = 1;
	n = 0;
	val = 0;
	while(splited_prompt[count] != NULL)
	{
		if(splited_prompt[count][0] == '-')
		{
			if (splited_prompt[count][1] == 'n' && val == 0)
			{
				count++;
				n++;
				}
			else
			{
				ft_putstr_fd(splited_prompt[count], 1);
				count++;
				val++;
			}
			}
			else
			{
				ft_putstr_fd(splited_prompt[count], 1);
				write(1, " ", 1);
				count++;
				val++;
			}
		}
		if(n == 0)
		write(1, "\n", 1);
} */

void	bt_echo(char **splited_prompt)
{
	int	count;
	int	n_flag;
	int	val;

	count = 0;
	n_flag = 0;
	val = 0;
	handle_echo_arguments(splited_prompt, &count, &n_flag, &val);

	if (n_flag == 0)
		write(1, "\n", 1);
}

void	handle_echo_arguments(char **splited_prompt,
				int *count, int *n_flag, int *val)
{
	while (splited_prompt[*count] != NULL)
	{
		if (is_n_flag(splited_prompt[*count], *val))
		{
			(*count)++;
			(*n_flag)++;
		}
		else
		{
			print_argument(splited_prompt[*count], val);
			(*count)++;
		}
	}
}

int	is_n_flag(char *arg, int val)
{
	return (arg[0] == '-' && arg[1] == 'n' && val == 0);
}

void	print_argument(char *arg, int *val)
{
	ft_putstr_fd(arg, 1);
	if ((*val) > 0)
		write(1, " ", 1);
	(*val)++;
}
