/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:21:07 by izanoni           #+#    #+#             */
/*   Updated: 2024/05/15 18:41:03 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

int main(int ac, char **av, char **envp)
{
	char *promptdado;
	int i = 0;
	int	aspas = 0;
	
	promptdado = readline("prompt: ");
	while(promptdado[i] != '\0')
	{
		if (promptdado[i] == 34 || promptdado[i] == 39)
		{
			if (promptdado[i] == 34)
			{
				i++;
				while (promptdado[i] != 34 && promptdado[i] != '\0')
					i++;
				if (promptdado[i] == 34)
					aspas = 0;
				else
					aspas = 1;
			}
			if (promptdado[i] == 39)
			{
				i++;
				while (promptdado[i] != 39 && promptdado[i] != '\0')
					i++;
				if (promptdado[i] == 39)
					aspas = 0;
				else
					aspas = 1;
			}
		}
		if (promptdado[i] == '\0')
			break ;
		i++;
	}
	i = 0;
	while (promptdado[i] != '\0')
	{
		while (promptdado[i] == 32)
			i++;
		while (promptdado[i] != 32 && promptdado[i] != '\0')
		{
			if (promptdado[i] == 34)
			{
				i++;
				while (promptdado[i] != 34)
					i++;
			}
			i++;
		}
	}
	if (aspas == 0)
		printf("fechô\n");
	if (aspas == 1)
		printf("não fechô\n");
	return (0);
	
}

char *strnchar(char *str, char c)
{
	int i = 0;
	
	while (str[i] != '\0')
	{
		if(str[i] == c)
			return(&str[i]);
		i++;
	}
	return(NULL);
}

/* int main(void)
{
	char *str;
	str = "bom dia mundão";
	printf("'%c'\n", *str);
	str = str + 3;
	printf("'%c'\n", *str);
	printf("'%c'\n", str[-3]);
	printf("'%c'\n", *(str - 3));
	str = "tchau";
	printf("'%c'\n", *str);
} */

/* int main(int ac, char **av, char **envp)
{
	char *path = "/usr/bin/clear";
	char *command[] = {"clear", NULL};
	char *env[] = {"TERM=xterm-256color", NULL};
	int fds[2];
	static char promptdado[29];
	
	pipe(fds);
	int pid_mini = fork();
	if (pid_mini == 0)
	{
		write(fds[1], "Mensagem escrita na criança\n", 29);
		printf("fd[0] da criança: %d\n", fds[0]);
		fds[0]++;
		printf("fd[0] da criança alterado: %d\n", fds[0]);
		exit(1) ;
	}
	printf("fd[0] do pai: %d\n", fds[0]);
	
	read(fds[0], promptdado, 29);
	printf("String que foi recebida pelo pai: %s", promptdado);
	
	// promptdado = readline("prompt: ");
	// printf("%s\n", promptdado);
	// execve(path, command, env);
	return (0);
} */
int	check_quotes(char *prompt)
{
	int i;
	
	i= 0;
	while(prompt[i] != '\0')
	{
		if (prompt[i] == 34 || prompt[i] == 39)
		{
			if (prompt[i] == 34)
			{
				i++;
				while (prompt[i] != 34 && prompt[i] != '\0')
					i++;
				if (prompt[i] == 34)
					aspas = 0;
				else
					aspas = 1;
			}
			if (prompt[i] == 39)
			{
				i++;
				while (prompt[i] != 39 && prompt[i] != '\0')
					i++;
				if (prompt[i] == 39)
					aspas = 0;
				else
					aspas = 1;
			}
		}
		if (prompt[i] == '\0')
			break ;
		i++;
	}
	if (aspas == 0)
		return (0);
	if (aspas == 1)
		return(-1);
}
