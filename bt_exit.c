/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:20:11 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/16 19:56:30 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_exit(t_minishell *s_minishell, t_fds	fd_redirect)
{
	int i;
	
	i = 0;
	if (s_minishell->current_command[2] != NULL)
	{
		print_error(s_minishell->current_command[0], ": too many arguments");
		s_minishell->exit_status = 2;
	}
	else if (s_minishell->current_command[1] != NULL)
	{
		while (ft_isalnum(s_minishell->current_command[1][i]) != 0)
			i++;
		if (s_minishell->current_command[1][i] != '\0' || i == 0)
		{
			print_error(s_minishell->current_command[0], ": numeric argument required");
			s_minishell->exit_status = 2;
		}
		else
			s_minishell->exit_status = ft_atoi(s_minishell->current_command[1]);
	}
	free_all(s_minishell->current_command);
	free_all(s_minishell->heredoc_names);
	free_all(s_minishell->splited_prompt);
	free_list(s_minishell->envp);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (fd_redirect.fd_out != STDOUT_FILENO)
		close (fd_redirect.fd_out);
	if (fd_redirect.fd_in != STDIN_FILENO)
		close (fd_redirect.fd_in);
	exit(s_minishell->exit_status);
}
/* 
	[1] existe? é numéico?
	[2] não pode existir

	se tem [1] valido é vai ser a "saida", não valido vai ser [2], não tem vai ser variavel já existente por ainda não descoberta
	exit status - numero de "saida" , vou descobrir
	free tudo
	close tudo (até std in e out)
	chamar função exit sistema com a variavel exit status
	
	
	
	close e free
	checar argumento, deve ser numérico (atoi)
 */