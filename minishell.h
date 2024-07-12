/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:13:50 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/12 19:57:58 by mgonzaga         ###   ########.fr       */
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

//bt_cd
int			bt_cd(t_minishell *s_minishell);
int			change_to_home_directory(t_env_list *envp, char *old_path);
int			change_directory(char *dir, t_env_list *envp, char *old_path);
void		update_wd(char *new_path, t_env_list *envp, char *old_path);

//bt_echo
void		bt_echo(t_minishell *s_minishell);
void		echo_n(int *n, int *count, int *val, char **splited_prompt);

//bt_env
int			bt_env(t_env_list *envp);

//bt_exit

//bt_export
void		bt_export(t_minishell	*s_minishell);
void		export_only(t_minishell *s_minishell);
void		find_inenvp_export(t_env_list *local, t_minishell *s_minishell, int *count, int	*i);
void		valid_export_var_name(int *count, int *i, char **splited_prompt);
size_t		ft_strlen_2(const char *s);

//bt_pwd
void		bt_pwd(void);

//bt_unset
char		*bt_unset(t_minishell *s_minishell);
void		process_prompt(char *prompt, t_env_list **envp);
int			should_remove_node(t_env_list *node, char *prompt, int len_var);
void		delnode(t_env_list	**envp, t_env_list	*node);
int			check_name(char *splited_prompt);

//check_command
int			check_heredoc(char	**prompt);
int			find_pipe(char **splited_prompt);
int			check_prompt(char *prompt);

//check_input
int			check_pipes(char *prompt);
int			check_quotes(char *prompt);
int			check_redirect(char *prompt);
int			only_space(char *prompt);
int			check_empty(char *prompt);

//envp_funcitions
t_env_list	*localize_envp(t_env_list *envp, char *var);
int			valid_var(t_env_list *envp, char *var);

//error
void		print_error(char *var, char *message);
char		*create_error_message(char *var, char *message);

//exec_command2
void		bt_or_exec(t_minishell *s_minishell);
void		exec_bt(int bt_check, t_minishell *s_minishell);
int			check_builtin(char *splited_prompt);

//exec_command
char		**execve_envp(t_env_list *envp);
void		command_exec(t_minishell *s_minishell, t_fds fd_redirect);
char		*find_path(char *splited_prompt, t_env_list *envp);
char		*return_value(t_env_list	*envp, char *var);
void		more_command(t_minishell *s_minishell);
char		**get_command(char **splited_prompt);

//expand_var
void		move_matrix(char **splited_prompt, int start);
void		expand_var(char **splited_prompt, t_env_list *envp);
void		mod_quots(char *input);
void		remov_quots(char *input);
int			malloc_len(char	*input, t_env_list	*envp);

//expand_var2
void		malloc_len_process(char	*input, int *len, int *i, t_env_list *envp);
char		*malloc_var(char *input, t_env_list	*envp);
void		walk_simple_quote(int *i, char *input, char *result, int *len);
void		put_result(char *substr, int *len, t_env_list *envp, char *result);
char		*put_substr(int *i, char *input);

//free_all
void		free_all(char **malloc_string);
void		free_list(t_env_list *envp);

//heredoc
void		initialize_with_empty_strings(char **heredoc_name, int size);
char		*get_heredoc_name(void);
void		heredoc(t_minishell *s_minishell);
void		heredoc_process(int	*count, t_minishell *s_minishell, int *count_command, int *fd);

//init_minishell
int			main(int argc, char **argv, char **envp);
t_env_list	*duplic_envp(char	**envp);
void		handle_commands(t_minishell *s_minishell);
void		process_input(t_minishell *s_minishell);
void		minishell(t_minishell *s_minishell);

//norme_prompt
char		*norme_string(char *prompt);
char		*malloc_prompt(char *prompt);
void		norme_char(int *count, int *count_result, char	*result, char	*prompt);

//redirect
void		free_redirect(char **splited_prompt);
t_fds		find_redirect(char **splited_prompt);

//signals
void		handle_signals(void);
void		sig_ctrl_c(int sig);
void		end_heredoc(int sig);
void		sig_heredoc(void);
void		sig_execute(int child_pid);

//t_list_funcitions
void		ft_lstadd_back(t_env_list **lst, t_env_list *new);
t_env_list	*ft_lstlast(t_env_list *lst);
t_env_list	*ft_lstnew(void *content);
int			ft_lstsize(t_env_list *lst);

//redirect
void		free_redirect(char **splited_prompt);
t_fds		find_redirect(char **splited_prompt);

//utils_fincitions
void		ignore_quotes(int *count, char *prompt);
int			pipes_count(char **prompt);
void		new_prompt(char *prompt);

#endif