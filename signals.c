#include "minishell.h"

void	handle_signals(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	ctrl_c(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("",0);
	rl_redisplay();
}

void    end_heredoc(int sig)
{
    ft_putstr_fd("\n", STDOUT_FILENO);
    rl_on_new_line();
    rl_replace_line("",0);
    g_signal = sig;
    close(STDIN_FILENO); // Para de ler da readline
}

void    sig_heredoc(void)
{
    signal(SIGINT, end_heredoc);
}

void    sig_execute(int child_pid)
{
    if (child_pid == 0)
    {
        signal(SIGINT, SIG_DFL);
    }
    else
    {
        signal(SIGINT, SIG_IGN);
    }
}

/* void	define_execute_signals(int child_pid)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (child_pid == 0)
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL); */