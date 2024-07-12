/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:04:03 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/12 17:20:57 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *var, char *message)
{
	char	*temp;

	temp = create_error_message(var, message);
	if (!temp)
		return ;
	write(2, temp, ft_strlen(temp));
	free(temp);
}

char	*create_error_message(char *var, char *message)
{
	int		len;
	int		count;
	char	*temp;

	len = ft_strlen(var) + ft_strlen(message) + 3;
	temp = malloc((len + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	count = 0;
	temp[count++] = '\'';
	while (*var != '\0')
		temp[count++] = *var++;
	temp[count++] = '\'';
	while (*message != '\0')
		temp[count++] = *message++;
	temp[count++] = '\n';
	temp[count] = '\0';
	return (temp);
}
