/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bt_or_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:28:04 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/24 13:19:59 by izanoni          ###   ########.fr       */
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

char	*put_substr(int *i, char *input)
{
	int		var_len;
	char	*substr;

	(*i)++;
	var_len = (*i);
	while ((ft_isalnum(input[var_len]) == 1 || input[var_len] == '_')
		&& input[var_len] != '\0')
		var_len++;
	substr = ft_substr(input, (*i), var_len - (*i));
	(*i) = var_len;
	return (substr);
}

size_t	ft_strlen_2(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '=')
		i++;
	return (i);
}
