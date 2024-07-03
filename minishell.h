/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:13:50 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/03 16:34:35 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include <signal.h>

# include "./libft/libft.h"

#define EXIT "exit"
#define ECHO "echo"
#define PWD "pwd"
#define ENV "env"
#define CD "cd"
#define EXPORT "export"
#define UNSET "unset"
#define DOUBLE_QUOTES '"'
#define SINGLE_QUOTES '\''

/*
enum e_special_characters
{
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '"'
};
*/

extern int g_signal;

typedef struct s_fd_in_out
{
	int fd_in;
	int fd_out;
}	t_fds;

typedef struct s_env_list
{
	char				*content;
	struct s_env_list	*next;
}	t_env_list;


struct s_minishell
{
	char		*input;
	char		*normalized_prompt;
	char		**splited_prompt;
	char        **current_command;
	t_env_list 	*envp;
	char        **heredoc_names;
	char		*current_heredoc;
	int            exit_status;
};
typedef struct s_minishell    t_minishell;


//minishell
void	minishell(t_minishell *s_minishell);
char	*norme_string(char *prompt);
char	*get_word(char *prompt, int *count);
int		count_word(char *prompt);
void	free_all(char **malloc_string);
void	command_exec(t_minishell *s_minishell, t_fds fd_redirect);
char	*find_path(char *splited_prompt, t_env_list	*envp);
char	*return_value(t_env_list *envp, char *var);
char	**ft_split(char const *s, char c);
char	*get_word1(char const *s, char c);
int		count_words1(char const *s, char c);
int		find_pipe(char **splited_prompt);
char	**get_command(char **splited_prompt);
void	more_command(t_minishell *s_minishell);
void	bt_or_exec(t_minishell *s_minishell);
void	ft_putstr_fd(char *s, int fd);
t_env_list	*duplic_envp(char **envp);
char	*put_expand(t_env_list *envp, char *splited_prompt);
char	*expand_var2(t_env_list *envp, char **splited_promp);
int  	pipes_count(char **prompt);
void 	new_prompt(char *prompt);
void	exec_bt(int bt_check, char **splited_prompt, t_env_list *envp);
int		check_builtin(char *splited_prompt);
void	free_list(t_env_list *envp);
void	norme_char(int *count, int *count_result, char	*result, char	*prompt);
char	*malloc_prompt(char *prompt);
void get_heredoc_names(t_minishell *s_minishell);
void process_heredocs(t_minishell *s_minishell);

//redirect
t_fds	find_redirect(char **splited_prompt);
void	free_redirect(char **splited_prompt);

//check_things
int		check_prompt(char *prompt);
int		check_quotes(char *prompt);
int		check_empty(char *prompt);
int		check_redirect(char *prompt);
int		only_space(char *prompt);
int		check_pipes(char *prompt);

//bt_unset
char	*bt_unset(char **splited_prompt, t_env_list	**envp);
int		should_remove_node(t_env_list *node, char *prompt, int len_var);
void	process_prompt(char *prompt, t_env_list **envp);
int		check_name(char *splited_prompt);
void	delnode(t_env_list	**envp, t_env_list	*node);

//bt_cd
int		bt_cd(char **splited_prompt, t_env_list *envp);
int		change_directory(char *dir, t_env_list *envp, char *old_path);
int		change_to_home_directory(t_env_list *envp, char *old_path);
void	update_wd(char *new_path , t_env_list *envp, char *old_path);

//bt_export
void	bt_export(char **splited_prompt, t_env_list	*envp);
int		valid_var(t_env_list *envp, char *var);
t_env_list	*localize_envp(t_env_list	*envp, char *var);
size_t	ft_strlen_2(const char *s);

//bt_pwd
void	bt_pwd(void);

//bt_exit

//bt_env
int		bt_env(t_env_list *envp);

//bt_echo
void	bt_echo(char **splited_prompt);


//error
void	print_error(char *var, char *message);

// functions.c
void	ft_lstadd_back(t_env_list **lst, t_env_list *new);
t_env_list	*ft_lstlast(t_env_list *lst);
t_env_list	*ft_lstnew(void *content);
int		ft_lstsize(t_env_list *lst);

// expandvar
void	mod_quots(char *input);
void expand_var(char **splited_prompt, t_env_list *envp);
void	remov_quots(char *input);
char *malloc_var(char	*input, t_env_list	*envp);
int malloc_len(char	*input, t_env_list	*envp);
void	heredoc(t_minishell *s_minishell);
int check_heredoc(char	**prompt);
void    initialize_with_empty_strings(char **heredoc_name, int size);
char    *get_heredoc_name(void);

// signals
void	handle_signals(void);
void	ctrl_c(int sig);


#endif