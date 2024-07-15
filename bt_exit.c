/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:20:11 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/15 20:17:58 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*bt_exit(t_minishell *s_minishell)
{
	s_minishell->current_command; 
	s_minishell->exit_status;
	
	[1] existe? é numéico?
	[2] não pode existir

	se tem [1] valido é vai ser a "saida", não valido vai ser [2], não tem vai ser variavel já existente por ainda não descoberta
	exit status - numero de "saida" , vou descobrir
	free tudo
	close tudo (até std in e out)
	chamar função exit sistema com a variavel exit status
}

	close e free
	checar argumento, deve ser numérico (atoi)