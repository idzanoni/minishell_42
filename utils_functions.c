/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:06:53 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/12 17:08:13 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ignore_quotes(int *count, char *prompt)
{
	char quote;
	
	quote = prompt[(*count)];
	while (prompt[(*count)] != quote)
		(*count)++;
}