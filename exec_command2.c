/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:33:42 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/22 17:04:19 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_or_exec(t_minishell *s_minishell)
{
	t_fds	fd_redirect;

	if (s_minishell->current_command != NULL
		&& s_minishell->current_command[0] != NULL)
		expand_var(s_minishell->current_command, s_minishell->envp, s_minishell);
	fd_redirect = find_redirect (s_minishell);
	if (fd_redirect.fd_in <= -1 || fd_redirect.fd_out <= -1)
	{
		if (fd_redirect.fd_in > -1 && fd_redirect.fd_in != STDIN_FILENO)
			close(fd_redirect.fd_in);
		if (fd_redirect.fd_out > -1 && fd_redirect.fd_out != STDOUT_FILENO)
			close(fd_redirect.fd_out);
		if (fd_redirect.fd_in != -2 && fd_redirect.fd_out != -2)
			perror("redirect");
		return ;
	}
	free_redirect(s_minishell->current_command);
	if(ft_strchr(s_minishell->current_command[0], ' ') != NULL)
	{
		char **temp = ft_split(s_minishell->current_command[0], ' ');
		int lines_temp = 0;
		while (temp[lines_temp] != NULL)
		{
			lines_temp++;
		}
		int lines_cmd = 0;
		while (s_minishell->current_command[lines_cmd] != NULL)
		{
			lines_cmd++;
		}
		char **temp2= s_minishell->current_command;
		s_minishell->current_command = malloc((lines_cmd + lines_temp) * sizeof(char *));
		int i = 0;
		while (temp[i] != NULL)
		{
			s_minishell->current_command[i] = temp[i];
			i++;
		}
		lines_temp = 1;
		while (temp2[lines_temp] != NULL)
		{
			s_minishell->current_command[i] = temp2[lines_temp];
			i++;
			lines_temp++;
		}
		s_minishell->current_command[i] = NULL;
		free(temp2[0]);
		free(temp);
		free(temp2);
	}
	if (s_minishell->current_command != NULL
		&& s_minishell->current_command[0] != NULL)
		exec_commands (s_minishell, fd_redirect);
	if (fd_redirect.fd_out != STDOUT_FILENO)
		close (fd_redirect.fd_out);
	if (fd_redirect.fd_in != STDIN_FILENO)
		close (fd_redirect.fd_in);
}

void	exec_commands(t_minishell *s_minishell, t_fds	fd_redirect)
{
	int		bt_check;

	bt_check = check_builtin(s_minishell->current_command[0]);
	if (bt_check > 0)
		exec_bt(bt_check, s_minishell, (fd_redirect));
	else
		command_exec(s_minishell, (fd_redirect));
}

void	exec_bt(int bt_check, t_minishell *s_minishell, t_fds fd_redirect)
{
	if (bt_check == 1)
		bt_exit(s_minishell, fd_redirect);
	if (bt_check == 2)
		bt_env(s_minishell, fd_redirect);
	if (bt_check == 3)
		bt_echo(s_minishell, fd_redirect);
	if (bt_check == 4)
		bt_pwd(s_minishell, fd_redirect);
	if (bt_check == 5)
		bt_cd(s_minishell);
	if (bt_check == 6)
		bt_export(s_minishell, fd_redirect);
	if (bt_check == 7)
		bt_unset(s_minishell);
}
