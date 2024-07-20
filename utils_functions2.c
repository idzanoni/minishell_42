/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:15:30 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/20 15:33:13 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	util_heredoc(char **limit, t_minishell *s_minishell,
			int *count, int *count_command)
{
	(*count)++;
	(*limit) = s_minishell->splited_prompt[(*count)];
	free(s_minishell->heredoc_names[(*count_command)]);
	s_minishell->heredoc_names[(*count_command)] = get_heredoc_name();
}
