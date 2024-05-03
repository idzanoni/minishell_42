/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renan.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:20:10 by izanoni           #+#    #+#             */
/*   Updated: 2024/05/03 15:06:35 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <sys/wait.h> 

char  *full_path(char *command, char **envp);

int main(int argc, char *argv[], char *envp[])
{
	char	*retorno_readline;
	char	**argumentos_do_comando;
	int		retorno_do_fork;
	char 	*caminho;
	
	while (42)
	{
		retorno_readline = readline("shellzinho: ");
		argumentos_do_comando = ft_split(retorno_readline, ' ');
		retorno_do_fork = fork();

		if (retorno_do_fork == 0)
		{
			caminho = ft_strjoin("/usr/bin/", argumentos_do_comando[0]);
			if (access(caminho, F_OK) == 0)
				execve(caminho, argumentos_do_comando, envp);
			exit(0);
		}
		wait(NULL);
		printf("-------------\n");
	}
	return (0);
}

char  *full_path(char *command, char **envp)
{
	
}
ok ki