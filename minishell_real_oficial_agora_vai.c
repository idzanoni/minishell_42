/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_real_oficial_agora_vai.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:46:48 by izanoni           #+#    #+#             */
/*   Updated: 2024/05/17 19:28:45 by izanoni          ###   ########.fr       */
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

void	print_matrix(char **matrix)
{
	for (int i = 0; matrix[i] != NULL; i++)
		printf("%s\n", matrix[i]);
}

void	minishell(char **envp)
{
	char	*prompt;
	char	*norme_prompt_result;
	char	**splited_prompt;

	while (1)
	{
		prompt = readline("shellzinho: "); // readline malloca (tem que dar free)
		if (!prompt)
		{
			break ;
		}
		else
		{
			if (check_prompt(prompt) < 0)
			{
				printf("error\n");
				//string vazia ( só \0, aspas, dados completos > < >> <<  | )
				free (prompt);
				continue ; //reset do while
			}
			//norme_prompt = norme_string(prompt);
		}
		norme_prompt_result = norme_string(prompt);
		free (prompt);
		if (norme_prompt_result == NULL)
		{
			printf("error\n");
			continue ;
		}
		splited_prompt = new_split(norme_prompt_result);
		if (!splited_prompt)
		{
			printf("error\n");
			free (norme_prompt_result);
			continue ;
		}
		free (norme_prompt_result);
		//print_matrix(splited_prompt);
		if(find_pipe(splited_prompt) == 1)
		{
			more_command(splited_prompt, envp);
		}
		else
			bt_or_exec(splited_prompt, envp);
		free_all (splited_prompt);
		printf("----\n");
	}
}

#define EXIT "exit"
#define ECHO "echo"
#define PWD "pwd"
#define ENV "env"
#define CD "cd"
#define EXPORT "export"
#define UNSET "unset"

int	check_builtin(char *splited_prompt)
{
	if (!ft_memcmp(splited_prompt, EXIT, ft_strlen(EXIT)))
		return (1);
	if (!ft_memcmp(splited_prompt, ENV, ft_strlen(ENV)))
		return (2);
	if (!ft_memcmp(splited_prompt, ECHO, ft_strlen(ECHO)))
		return (3);
	if (!ft_memcmp(splited_prompt, PWD, ft_strlen(PWD)))
		return (4);
	if (!ft_memcmp(splited_prompt, CD, ft_strlen(CD)))
		return (5);
	if (!ft_memcmp(splited_prompt, EXPORT, ft_strlen(EXPORT)))
		return (6);
	if (!ft_memcmp(splited_prompt, UNSET, ft_strlen(UNSET)))
		return (7);
	else
		return (0);
}

void	bt_or_exec(char **splited_prompt, char **envp)
{
	int		bt_check;
	t_fds	fd_redirect;

	// Validar redirects
	fd_redirect = find_redirect (splited_prompt);
	free_redirect(splited_prompt);

	// Expandir variáveis;
	bt_check = check_builtin(splited_prompt[0]);
	if (bt_check > 0)
	{
		// executar builtin
	}
	else
		command_exec(splited_prompt, envp);
}

void	free_redirect(char **splited_prompt)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while(splited_prompt[count] != NULL)
	{
		if(splited_prompt[count][0] == '<' || splited_prompt[count][0] == '>')
		{
			free(splited_prompt[count]);
			count++;
			free(splited_prompt[count]);
			i = count;
			while (splited_prompt[i] != NULL)
			{
				splited_prompt[i - 1] = splited_prompt[i + 1];
				i++;
			}		
			count = count - 2;
		}
		count++;
	}
}

t_fds find_redirec(char **splited_prompt)
{
	t_fds fd_redirect;
	int count;

	fd_redirect.fd_in = STDIN_FILENO;
	fd_redirect.fd_out = STDOUT_FILENO;
	count = 0;
	while (splited_prompt[count] != NULL)
	{
		if (splited_prompt[count][0] == '>')
		{
			if (fd_redirect.fd_out != STDOUT_FILENO)
				close (fd_redirect.fd_out);
			if (splited_prompt[count][1] == '>')
				fd_redirect.fd_out = open (splited_prompt[count + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				fd_redirect.fd_out = open (splited_prompt[count + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		else if (splited_prompt[count][0] == '<')
		{
			if (fd_redirect.fd_in != STDIN_FILENO)
				close (fd_redirect.fd_in);
			if (splited_prompt[count][1] == '<')
			{}
			else
				fd_redirect.fd_in = open (splited_prompt[count + 1], O_RDONLY);
		}
		count++;
	}
	return(fd_redirect);
}

int find_pipe(char **splited_prompt)
{
	int i;

	i = 0;
	while(splited_prompt[i] != NULL)
	{
		if (splited_prompt[i][0] == '|')
			return (1);
		i++;
	}
	return(0);
}

char	*norme_string(char *prompt)
{
	int		count;
	char	*result;
	int 	size_prompt;
	int		count_result;
	
	count = 0;
	count_result = 0;
	size_prompt = strlen(prompt); // usar ft_strlen
	while (prompt[count] != '\0')
	{
		if(prompt[count] == '>'|| prompt[count] == '<' || prompt[count] == '|')
			size_prompt = size_prompt + 2;
		count++;
	}
	result = malloc((size_prompt + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	count = 0;
	while (prompt[count] != '\0')
	{
		if (prompt[count] == '>'|| prompt[count] == '<' || prompt[count] == '|')
		{
			result[count_result] = ' ';
			count_result++;
			result[count_result] = prompt[count];
			if (prompt[count + 1] == '>' || prompt[count + 1] == '<')
			{
				count++;
				count_result++;
				result[count_result] = prompt[count];
				count_result++;
				result[count_result] = ' ';
				count++;
				count_result++;
			}
			else
			{
				count_result++;
				result[count_result] = ' ';
				count_result++;
				count++;
			}
		}
		else
		{
			result[count_result] = prompt[count];
			count++;
			count_result++;
		}
	}
	result[count_result] = '\0';
	return (result);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	minishell(envp);
	rl_clear_history();
	return (0);
}
