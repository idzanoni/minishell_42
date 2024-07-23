#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	s_minishell;

	(void)argc;
	(void)argv;
	ft_bzero(&s_minishell, sizeof(t_minishell));
	s_minishell.envp = duplic_envp(envp);
	minishell(&s_minishell);
	rl_clear_history();
	close(STDIN_FILENO);
	return (0);
}
