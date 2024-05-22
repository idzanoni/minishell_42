#ifndef MINISHELL
# define MINISHELL

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>


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
void    command_exec(char **splited_prompt, char **envp);
char	*find_path(char *splited_prompt, char **envp);
char	*return_value(char **envp, char *var);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	**ft_split(char const *s, char c);
char	*get_word1(char const *s, char c);
int		count_words1(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);

#endif