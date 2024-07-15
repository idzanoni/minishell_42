/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:22:25 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/12 19:59:57 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(void)
{
	signal(SIGINT, sig_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_ctrl_c(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("",0);
	rl_redisplay();
}

void	end_heredoc(int sig)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("",0);
	g_signal = sig;
	close(STDIN_FILENO); // Para de ler da readline
}

void	sig_heredoc(void)
{
	signal(SIGINT, end_heredoc);
}

void	sig_execute(int child_pid)
{
	if (child_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
	}
}
