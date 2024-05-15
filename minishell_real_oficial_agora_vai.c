/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_real_oficial_agora_vai.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:46:48 by izanoni           #+#    #+#             */
/*   Updated: 2024/05/15 19:41:00 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>

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
				check_quotes(prompt);

			}
		}
		printf("----\n");
	}
}

int	check_prompt(char *prompt)
{
	int		checker;
	
	//check_empty(prompt); // Comando está certo, não tem mensagem de erro
	checker = check_quotes(prompt);
	if (checker == -1)
	{
		printf("erro aspas\n"); // Se der ruim, tem que mostrar mensagem de erro
		return(-1);
	}
	//check_redirect(prompt); // Se der ruim, tem que mostrar mensagem de erro
	return(0);
}
int check_empty(char *prompt)
{
	if(prompt[0] == '\0')
		return(-1);
	else
		return(0);
}
int check_redirect(char *prompt)
{
	// echo   oi				 < 										      file
	// ls       				> file
	int count;

	count = 0;
	while(prompt[count] != '\0')
	{
		// ">            "
		if(prompt[count] == '>' || prompt[count] == '<')
		{
			
		}
		count++;
	}
	return(0);
}
/* int	check_quotes(char *prompt)
{
	int	count;
	int count_quotes;

	count = 0;
	count_quotes = 0;
	while(prompt[count] != '\0')
	{
		// echo oi "mensagem ' simples"
		if(prompt[count] == '"' || prompt[count] == '\'')
			count_quotes++;
	}
	if((count_quotes / 2) == 0)
		return(0);
	else
		return(-1);	
} */

int	check_quotes(char *prompt)
{
	int i;
	int quotes;
	
	i = 0;
	while(prompt[i] != '\0')
	{
		if (prompt[i] == 34 || prompt[i] == 39)
		{
			if (prompt[i] == 34)
			{
				i++;
				while (prompt[i] != 34 && prompt[i] != '\0')
					i++;
				if (prompt[i] != 34)
					quotes = -1;
			}
			if (prompt[i] == 39)
			{
				i++;
				while (prompt[i] != 39 && prompt[i] != '\0')
					i++;
				if (prompt[i] != 39)
					quotes = -1;
			}
		}
		if (prompt[i] == '\0')
			break ;
		i++;
	}
	return(quotes);
}

int	main(int argc, char **argv, char **envp)
{
	minishell(envp);
	return (0);
}