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
{
    
}
char	*bt_export(char **splited_prompt, t_fds command_fd)
{

    int	count;
	int i;

	count = 0;
	i = 1
    if(splited_prompt[1] == NULL)
    {
        FUNÇÃO ENV
    }
    else
    {
        while(splited_prompt[count] != NULL)
		{
			if(ft_isalpha(splited_prompt[count][0] || splited_prompt[count][0] == '_')
			{
				while(splited_prompt[count][i] != '\0')
				{
					if(ft_isalpha(splited_prompt[count][0] || splited_prompt[count][0] == '_' || 
					ft_isalnum(splited_prompt[count][i])
						i++;
					else
						ft_putstr_fd("export: splited_pront[count]: not a valid identifier", 1);
				}	
			}
			else
				ft_putstr_fd("export: splited_pront[count]: not a valid identifier", 1)
		}
			
            // Validar o que foi digitado
                // EXEMPLO: VAR=42 (tem que validar que VAR é um nome de variável válido)
            // Verificar se a variável existe no envp
                // Se não existir, adiciona no envp o que foi digitado (VAR=42)
                // Se existir... executa e dá uma olhada no que acontece

    }
}
char	*bt_unset(char *splited_prompt, t_fds command_fd);
char	*bt_env(char *splited_prompt, t_fds command_fd);
char	*bt_exit(char *splited_prompt, t_fds command_fd);