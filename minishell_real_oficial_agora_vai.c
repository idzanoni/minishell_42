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

void	minishell(char **envp)
{
	char	*prompt;
	char	*norme_prompt_result;

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
		printf("%s\n", norme_prompt_result);
		(void)envp;
		printf("----\n");
	}
	
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
	// result = echo oi >%$$&&$%$$@
	// prompt = echo oi>>file|ls
	while (prompt[count] != '\0')
	{
		if (prompt[count] == '>'|| prompt[count] == '<' || prompt[count] == '|')
		{
			result[count_result] = ' '; // result que esta recebendo o novo valor
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
	/* while (result[count_result] != '\0')
	{
		result[count_result] = '\0';
		count_result++;
	} */
	result[count_result] = '\0';
	return (result);
}

int	check_prompt(char *prompt)
{
	if (check_empty(prompt))
		return (-1);
	add_history(prompt);
	if (only_space(prompt))
		return (-1);
	if (check_quotes(prompt))
		return (-1);
	if (check_redirect(prompt))
		return (-1);
	if (check_pipes(prompt))
		return (-1);
	return (0);
}

int	check_empty(char *prompt)
{
	if (prompt[0] == '\0')
		return (-1);
	else
		return (0);
}

int	only_space(char *prompt)
{
	int count;

	count = 0;
	while (prompt[count] != '\0')
	{
		if (prompt[count] != ' ' || prompt[count] != '\t') 
			return(0);
		count++;
	}
	return (-1);
}  

int	check_redirect(char *prompt)
{
	int		count;
	char	quote;

	count = 0;
	while(prompt[count] != '\0')
	{
		if (prompt[count] == 34 || prompt[count] == 39)
		{
			quote = prompt[count];
			while (prompt[count] != quote)
				count ++;
		}
		if(prompt[count] == '>' || prompt[count] == '<')
		{
			count++;
			if ((prompt[count] != prompt[count - 1]) && (prompt[count] == '>' || prompt[count] == '<'))
				return(-1);
			else if (prompt[count] == '>' || prompt[count] == '<')
				count++;
			while (prompt[count] == ' ' || prompt[count] == '\t')
				count++;
			if(prompt[count] == '\0' || prompt[count] == '|' 
				|| prompt[count] == '>' || prompt[count] == '<')
			{
				printf("error redirect\n");
				return(-1);
			}
		}
		count++;
	}
	return(0);
}

int	check_quotes(char *prompt)
{
	int i;
	int quotes;
	int	checker;
	
	checker = 0;
	i = -1;
	while (prompt[++i] != '\0')
	{
		if (prompt[i] == 34 || prompt[i] == 39)
		{
			quotes = prompt[i];
			if (prompt[i] == 34)
				while (prompt[++i] != 34 && prompt[i] != '\0')
					;
			else if (prompt[i] == 39)
				while (prompt[++i] != 39 && prompt[i] != '\0')
					;
			if (prompt[i] != quotes)
				checker = -1;
		}
		if (prompt[i] == '\0')
			break ;
	}
	return (checker);
}

int	check_pipes(char *prompt)
{
	/***
		// errado
		|
		| echo oi
		echo oi |
		| |
		echo oi "> file | ls" | ls |      
		           | echo oi
		echo oi |        | ls

		// correto
		ls | echo
		ls | > file
		ls|>file
		echo | echo | << file | echo
		"ls"|"  "|ls
	 */

	int 	count;
	char	quote;

	count = 0;
	while (prompt[count] == ' ' || prompt[count] == '	')
		count++;
	if (prompt[count] == '|')
		return (-1);
	while(prompt[count] != '\0')
	{
		if (prompt[count] == 34 || prompt[count] == 39)
		{
			quote = prompt[count];
			while (prompt[count] != quote)
				count ++;
		}
		if (prompt[count] == '|')
		{
			count++;
			while (prompt[count] == ' ' || prompt[count] == '	')
				count++;
			if (prompt[count] == '\0' || prompt[count] == '|')
				return (-1);
		}
		else
			count++;
	}
	return (0);
}

//char	**new_split(char *prompt)
//{
	/***
	 TODO: 
	contar "palavras"
	  - checar aspas
	criar o primeiro malloc
	mallocar cada "palavra"
	  - checar aspas

	*/
//}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	minishell(envp);
	return (0);
}
