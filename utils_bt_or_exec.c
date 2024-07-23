/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bt_or_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:28:04 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/23 17:23:20 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_fds fd_redirect)
{
	if (fd_redirect.fd_in > -1 && fd_redirect.fd_in != STDIN_FILENO)
		close(fd_redirect.fd_in);
	if (fd_redirect.fd_out > -1 && fd_redirect.fd_out != STDOUT_FILENO)
		close(fd_redirect.fd_out);
	if (fd_redirect.fd_in != -2 && fd_redirect.fd_out != -2)
		perror("redirect");
}

void	expand_with_command(t_minishell *s_minishell)
{
	char	**temp;
	char	**temp2;
	int		lines_temp;
	int		lines_cmd;

	temp = ft_split(s_minishell->current_cmd[0], ' ');
	temp2 = s_minishell->current_cmd;
	lines_temp = 0;
	lines_cmd = 0;
	while (temp[lines_temp] != NULL)
		lines_temp++;
	while (s_minishell->current_cmd[lines_cmd] != NULL)
		lines_cmd++;
	s_minishell->current_cmd = malloc((lines_cmd + lines_temp)
			* sizeof(char *));
	lines_cmd = -1;
	while (temp[++lines_cmd] != NULL)
		s_minishell->current_cmd[lines_cmd] = temp[lines_cmd];
	lines_temp = 1;
	while (temp2[lines_temp] != NULL)
		s_minishell->current_cmd[lines_cmd++] = temp2[lines_temp++];
	s_minishell->current_cmd[lines_cmd] = NULL;
	free(temp2[0]);
	free(temp);
	free(temp2);
}
