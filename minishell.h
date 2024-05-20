#ifndef MINISHELL
# define MINISHELL

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
int		check_prompt(char *prompt);
int		check_quotes(char *prompt);
int		check_empty(char *prompt);
int		check_redirect(char *prompt);
int		only_space(char *prompt);
int		check_pipes(char *prompt);
char	*norme_string(char *prompt);
char	**new_split(char *prompt);
char	*get_word(char *prompt, int *count);
int		count_word(char *prompt);
void	free_all(char **malloc_string);

#endif