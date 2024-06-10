#include "minishell.h"

void	bt_echo(char **splited_prompt)
{
    int count;
    int n;
    int val;

    count = 1;
    n = 0;
    val = 0;
    while(splited_prompt[count] != NULL)
    {
        if(splited_prompt[count][0] == '-')
        {
            if(splited_prompt[count][1] == 'n' && val == 0)
            {    
                count++;
                n++;
            }
            else
            {
                ft_putstr_fd(splited_prompt[count], 1);
                count++;   
                val++;
            }
        }
        else
        {
            ft_putstr_fd(splited_prompt[count], 1);
            count++;
			val++;  
        }
    }
    if(n == 0)
        write(1, "\n", 1);
}


void    bt_pwd(void)
{
    char    *path;
    
    path = getcwd(NULL, 0);
    ft_putstr_fd(path, 1);
    ft_putstr_fd("\n", 1);
}

char	*bt_cd(char *splited_prompt, t_fds command_fd);
char	*bt_unset(char *splited_prompt, t_fds command_fd);
char	*bt_env(char *splited_prompt, t_fds command_fd);
char	*bt_exit(char *splited_prompt, t_fds command_fd);