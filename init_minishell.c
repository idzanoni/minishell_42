/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:46:48 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/01 19:34:15 by mgonzaga         ###   ########.fr       */
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

void	minishell(t_minishell *s_minishell)
{
	while (1)
	{
		s_minishell->input = readline("shellzinho: ");
		if (!s_minishell->input)
		{
			free_list(s_minishell->envp);
			break ;
		}
		else
		{
			if (check_prompt(s_minishell->input) < 0)
			{
				free (s_minishell->input);
				continue ;
			}
		s_minishell->normalized_prompt = norme_string(s_minishell->input);
		}
		free (s_minishell->input);
		if (s_minishell->normalized_prompt == NULL)
		{
			printf("error\n");
			continue ;
		}
		new_prompt(s_minishell->normalized_prompt);
		s_minishell->splited_prompt = ft_split(s_minishell->normalized_prompt, -42);
		if (!s_minishell->splited_prompt)
		{
			printf("error\n");
			free (s_minishell->normalized_prompt);
			continue ;
		}
		free (s_minishell->normalized_prompt);
		if (check_heredoc(s_minishell->splited_prompt) == 1)
			heredoc(s_minishell);
		if (find_pipe(s_minishell->splited_prompt) == 1)
		{
			more_command(s_minishell);
		}
		else
			bt_or_exec(s_minishell);
		free_all (s_minishell->splited_prompt);
	}
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

int	main (int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_minishell s_minishell;

	s_minishell.envp = duplic_envp(envp);
	handle_signals();
	minishell(&s_minishell);
	rl_clear_history();
	return (0);
}
