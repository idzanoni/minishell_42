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

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


/*
#define DOUBLE_QUOTES '"'
#define SINGLE_QUOTES '\''

enum e_special_characters
{
	JANEIRO = 1,
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '"'
};
*/

void	minishell(char **envp);
int	check_prompt(char *prompt);
int	check_quotes(char *prompt);
int check_empty(char *prompt);
int check_redirect(char *prompt);

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

	while (1)
	{
		prompt = readline("shellzinho: ");
		if (!prompt)
		{
			break ;
		}
		else
		{
			if (check_prompt(prompt))
			{
				//string vazia ( só \0, aspas, dados completos > < >> <<  | )
			
			}
		}
		printf("----\n");
	}
}

int	check_prompt(char *prompt)
{
	if (!check_empty(prompt)) // check_empty == 0 ?
		return (-1); // Comando está certo, não tem mensagem de erro
	add_history(prompt);
	if (!check_quotes(prompt))
		return (-1);
	//check_redirect(prompt);
	 // Se der ruim, tem que mostrar mensagem de erro
	return(0);
}
int check_empty(char *prompt)
{
	if(prompt[0] == '\0')
	{	
		//printf("Error empty\n");
		return(-1);
	}
	else
		return(0);
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

int check_redirect(char *prompt)
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
	
	quotes = 0;
	i = -1;
	while(prompt[++i] != '\0')
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
				quotes = -1;
		}
		if (prompt[i] == '\0')
			break ;
	}
	return(quotes);
}

int	main(int argc, char **argv, char **envp)
{
	minishell(envp);
	return (0);
}
