/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:27:02 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/06/24 14:16:49 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(char	*limit)
{
	char	*comp;
	
	while(ft_memcmp(limit, comp, ft_strlen(limit)) != 0)
	{
		comp = readline("heredoc:");
		
		//ft_putstr_fd(comp, 1);
	}
}