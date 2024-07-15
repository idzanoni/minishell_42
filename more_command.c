/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:54:57 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/15 13:11:36 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// função more_comand separada pelo gpt


void more_command(t_minishell *s_minishell)
{
	int count_pipes = count_pipes_in_prompt(s_minishell->splited_prompt);
	int *fork_return = malloc((count_pipes + 2) * sizeof(int));

	if (!fork_return)
		return;

	execute_commands(s_minishell, count_pipes, fork_return);
	wait_for_children(fork_return);

	free(fork_return);
}

int count_pipes_in_prompt(char **splited_prompt)
{
	int count_pipes = 0;
	int i = 0;

	while (splited_prompt[i] != NULL)
	{
		if (splited_prompt[i][0] == '|')
			count_pipes++;
		i++;
	}
	return count_pipes;
}

void execute_commands(t_minishell *s_minishell, int count_pipes, int *fork_return)
{
	int fds[2];
	int fd_bkp = STDIN_FILENO;
	int j = 0;

	while (count_pipes >= 0)
	{
		if (count_pipes > 0)
			pipe(fds);

		fork_return[j] = fork();

		if (fork_return[j] == 0)
		{
			handle_child_process(s_minishell, count_pipes, fds, fd_bkp);
		}
		else
		{
			handle_parent_process(s_minishell, fds, &fd_bkp, count_pipes);
			count_pipes--;
			j++;
		}
	}

	fork_return[j] = -42;
}

void	handle_child_process(t_minishell *s_minishell, int count_pipes,
	int fds[2], int fd_bkp)
{
	rl_clear_history();
	s_minishell->current_command = get_command(s_minishell->splited_prompt);
	free_all(s_minishell->splited_prompt);

	if (count_pipes > 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		close(fds[0]);
	}

	dup2(fd_bkp, STDIN_FILENO);
	if (fd_bkp != STDIN_FILENO)
		close(fd_bkp);

	bt_or_exec(s_minishell);

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free_all(s_minishell->current_command);
	free_list(s_minishell->envp);
	exit(142);
}

void	handle_parent_process(t_minishell *s_minishell, int fds[2],
	int *fd_bkp, int count_pipes)
{
	free_all(get_command(s_minishell->splited_prompt));

	if (*fd_bkp != STDIN_FILENO)
		close(*fd_bkp);

	*fd_bkp = fds[0];

	if (count_pipes > 0)
		close(fds[1]);
}

void	wait_for_children(int *fork_return)
{
	int	i;

	i = 0;
	while (fork_return[i] != -42)
	{
		waitpid(fork_return[i], NULL, 0);
		i++;
	}
}
