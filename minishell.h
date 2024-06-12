#ifndef MINISHELL
# define MINISHELL

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>					

#define DOUBLE_QUOTES '"'
#define SINGLE_QUOTES '\''

/*
enum e_special_characters
{
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '"'
};
*/
typedef struct s_fd_in_out
{
	int fd_in;
	int fd_out;
} t_fds;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void	minishell(t_list	*envp);
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
void    command_exec(char **splited_prompt, t_list	*envp, t_fds fd_redirect);
char	*find_path(char *splited_prompt, t_list	*envp);
char	*return_value(t_list	*envp, char *var);
char	**ft_split(char const *s, char c);
char	*get_word1(char const *s, char c);
int		count_words1(char const *s, char c);
int		find_pipe(char **splited_prompt);
char	**get_command(char **splited_prompt);
void	more_command(char **splited_prompt, t_list	*envp);
void	bt_or_exec(char **splited_prompt, t_list *envp);
t_fds	find_redirect(char **splited_prompt);
void	free_redirect(char **splited_prompt);
void	bt_echo(char **splited_prompt);
void	ft_putstr_fd(char *s, int fd);
void    bt_pwd(void);
int 	valid_var(t_list	*envp, char *var);
t_list 	*localize_envp(t_list	*envp, char *var);
void	bt_export(char **splited_prompt, t_list	*envp);
t_list	*duplic_envp(char	**envp);


// functions.c
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strdup(const char *s);
size_t	ft_strlen_2(const char *s);
int		ft_isalpha(int i);
int		ft_isalnum(int i);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	ft_putendl_fd(char *s, int fd);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
int	ft_lstsize(t_list *lst);





#endif