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
 *				🚀🚀🚀 O MELHOR MINISHELL DO BRASIL 🚀🚀🚀				*
 *																		*
 ***********************************************************************/

/************************************************************************
 *																		*
 *				  💻💻💻 Feito por Humanas Coders 💻💻💻				*
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
				continue ; //reset do while
			}
			//norme_prompt = norme_string(prompt);
		}
		norme_prompt_result = norme_string(prompt);
		if (norme_prompt_result == NULL)
		{
			printf("error");
			continue ;
		}
		splited_prompt = new_split(norme_prompt_result);
		{
			printf("error");
			continue ;
		}		
		//print_matrix(splited_prompt);
		command_exec(splited_prompt, envp);
		(void)envp;
		printf("----\n");
	
	}
	
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
	return (0);
}
