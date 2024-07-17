/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:46:48 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/17 17:22:48 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/************************************************************************
 *																		*
 *				🚀🚀🚀 O MELHOR MINISHELL DO BRASIL 🚀🚀🚀			 *
 *																		*
 ***********************************************************************/

/************************************************************************
 *																		*
 *				  💻💻💻 Feito por Humanas Coders 💻💻💻			 *
 *																		*
 ***********************************************************************/

int    g_signal = 0;

void minishell(t_minishell *s_minishell)
{
	while (1)
	{
		s_minishell->input = readline("shellzinho: ");
		if (!s_minishell->input)
		{
			free_list(s_minishell->envp);
			break ;
		}
		process_input(s_minishell);
	}
}

void	process_input(t_minishell *s_minishell)
{
	if (check_prompt(s_minishell->input) < 0)
	{
		free(s_minishell->input);
		return ;
	}
	s_minishell->normalized_prompt = norme_string(s_minishell->input);
	free(s_minishell->input);
	if (!s_minishell->normalized_prompt)
	{
		printf("error\n");
		return ;
	}
	new_prompt(s_minishell->normalized_prompt);
	s_minishell->splited_prompt = ft_split(s_minishell->normalized_prompt, -42);
	free(s_minishell->normalized_prompt);
	if (!s_minishell->splited_prompt)
	{
		printf("error\n");
		return ;
	}
	handle_commands(s_minishell);
	free_all(s_minishell->splited_prompt);
}

void handle_commands(t_minishell *s_minishell)
{
	if (check_heredoc(s_minishell->splited_prompt) == 1)
	{
		if(heredoc(s_minishell) == 1)
			return ;
	}
	if (find_pipe(s_minishell->splited_prompt) == 1)
		more_command(s_minishell);
	else
	{
		s_minishell->current_command = s_minishell->splited_prompt;
		s_minishell->splited_prompt = NULL;
		if (s_minishell->heredoc_names != NULL)
		{
			s_minishell->current_heredoc = s_minishell->heredoc_names[0];
			s_minishell->heredoc_names = NULL;
		}
		bt_or_exec(s_minishell);
		free (s_minishell->current_heredoc);
		s_minishell->current_heredoc = NULL;
	}
	if (s_minishell->heredoc_names != NULL)
		free_all(s_minishell->heredoc_names);
	s_minishell->heredoc_names = NULL;
	free_all(s_minishell->current_command);
}

t_env_list	*duplic_envp(char	**envp)
{
	int			count_lines;
	t_env_list	*new_envp;

	new_envp = NULL;
	count_lines = 0;
	while (envp[count_lines] != NULL)
	{
		if (new_envp == NULL)
			new_envp = ft_lstnew(ft_strdup(envp[count_lines]));
		else
			ft_lstadd_back(&new_envp, ft_lstnew(ft_strdup(envp[count_lines])));
		count_lines++;
	}
	return (new_envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	s_minishell;

	(void)argc;
	(void)argv;
	ft_bzero(&s_minishell, sizeof(t_minishell));
	s_minishell.envp = duplic_envp(envp);
	handle_signals();
	minishell(&s_minishell);
	rl_clear_history();
	return (0);
}
