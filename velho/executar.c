/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:01:23 by izanoni           #+#    #+#             */
/*   Updated: 2024/05/02 16:08:04 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <sys/wait.h> 

int main(int argc, char *argv[], char *envp[])
{
	char	*retorno_readline;
	char	**argumentos_do_comando;

	retorno_readline = readline("Pastel de Flango: ");
	printf("Isso é o que a readline retornou: %s\n\n", retorno_readline);

	// O que foi acrescentado
	argumentos_do_comando = ft_split(retorno_readline, ' ');
	printf("Foi tudo picotado!\n");


	printf("-------------\n");
	execve("/usr/bin/ls", argumentos_do_comando, NULL);
	return (0);
}