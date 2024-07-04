/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:33:42 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/04 19:51:36 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_or_exec(t_minishell *s_minishell)
{
	int		bt_check;
	t_fds	fd_redirect;

	fd_redirect = find_redirect (s_minishell->current_command);
	free_redirect(s_minishell->current_command);
	expand_var(s_minishell->current_command, s_minishell->envp);
	if (s_minishell->current_command != NULL
		&& s_minishell->current_command[0] != NULL)
	{	
		bt_check = check_builtin(s_minishell->current_command[0]);
		if (bt_check > 0)
			exec_bt(bt_check, s_minishell);
		else
			command_exec(s_minishell, fd_redirect);
	}
	if (fd_redirect.fd_out != STDOUT_FILENO)
		close (fd_redirect.fd_out);
	if (fd_redirect.fd_in != STDIN_FILENO)
		close (fd_redirect.fd_in);
}

void	exec_bt(int bt_check, t_minishell *s_minishell)
{
	if (bt_check == 3)
		bt_echo(s_minishell->splited_prompt);
	if (bt_check == 4)
		bt_pwd();
	if (bt_check == 6)
		bt_export(s_minishell);
	if (bt_check == 7)
		bt_unset(s_minishell->splited_prompt, &s_minishell->envp);
	if (bt_check == 5)
		bt_cd(s_minishell->splited_prompt, s_minishell->envp);
}

int	check_builtin(char *splited_prompt)
{
	if (!ft_memcmp(splited_prompt, EXIT, ft_strlen(EXIT)))
		return (1);
	if (!ft_memcmp(splited_prompt, ENV, ft_strlen(ENV)))
		return (2);
	if (!ft_memcmp(splited_prompt, ECHO, ft_strlen(ECHO)))
		return (3);
	if (!ft_memcmp(splited_prompt, PWD, ft_strlen(PWD)))
		return (4);
	if (!ft_memcmp(splited_prompt, CD, ft_strlen(CD)))
		return (5);
	if (!ft_memcmp(splited_prompt, EXPORT, ft_strlen(EXPORT)))
		return (6);
	if (!ft_memcmp(splited_prompt, UNSET, ft_strlen(UNSET)))
		return (7);
	else
		return (0);
}
