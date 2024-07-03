/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:04:03 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/03 16:57:02 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	print_error(char *var, char *message)
{
	int len;
	int count;
	char *temp;

	count = 0;
	len = ft_strlen(var) + ft_strlen(message) + 2;
	temp = malloc((len+2) * sizeof(char));
	if (!temp)
		return ;
	len = 0;
	temp[count] = '\'';
	while (var[len] != '\0')
	{
		count++;
		temp[count] = var[len];
		len++;
	}
	temp[count++] = '\'';
	len = 0;
	while(message[len] != '\0')
	{
		temp[count] = message[len];
		count++;
		len++;
	}
	temp[count] = '\n';
	temp[++count] = '\0';
	write(2,temp,ft_strlen(temp));
	free(temp);
} */

void print_error(char *var, char *message)
{
	char *temp;
	
	temp = create_error_message(var, message);
	if (!temp)
		return;
	write(2, temp, ft_strlen(temp));
	free(temp);
}

char *create_error_message(char *var, char *message)
{
	int len;
	
	len = ft_strlen(var) + ft_strlen(message) + 3;
	char *temp = malloc((len + 1) * sizeof(char));
	if (!temp)
		return NULL;
	
	int count = 0;
	temp[count++] = '\'';
	while (*var != '\0')
		temp[count++] = *var++;
	temp[count++] = '\'';
	while (*message != '\0')
		temp[count++] = *message++;
	temp[count++] = '\n';
	temp[count] = '\0';
	
	return temp;
}
