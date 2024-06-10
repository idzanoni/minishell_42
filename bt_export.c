#include "minishell.h"

void	bt_export(char **splited_prompt, char	**envp)
{

    int	count;
	int i;
	int	envp_count;

	count = 1;
	i = 1;
	envp_count = 0;
    if(splited_prompt[1] == NULL)
    {
        ft_putstr_fd("Não Fiz ainda", 1);
    }
    else
    {
        while(splited_prompt[count] != NULL)
		{
			printf("%d", splited_prompt[count][0]);
			if(ft_isalpha(splited_prompt[count][0]) == 1 || splited_prompt[count][0] == '_')
			{
				while(splited_prompt[count][i] != '\0' || splited_prompt[count][i] != '=')
				{
					if(ft_isalpha(splited_prompt[count][i]) == 1 || splited_prompt[count][i] == '_' || ))
                    {   
						if(splited_prompt[count][i] != '\0' || splited_prompt[count][i] == '_')
							break;
					    i++;
					}
					else
                    {
						if(splited_prompt[count][i] != '\0' || splited_prompt[count][i] == '_')
							break;
                        ft_putstr_fd("export: not a valid identifier", 1);
                        break;
                    }
                }
				i = 1;
                if(valid_var(envp, splited_prompt[count]) == 1)
				{
					if(splited_prompt[count][i] == '=')
					{
						free(envp[localize_envp(envp, splited_prompt[count])]);
						envp[localize_envp(envp, splited_prompt[count])] = malloc(ft_strlen(splited_prompt[count] + 1 * sizeof(char *)));
						ft_memcpy(envp[localize_envp(envp, splited_prompt[count])], splited_prompt[count], ft_strlen(splited_prompt[count]));
					}
				}
				else
				{
					while(envp[envp_count] != NULL)
						envp_count++;
					envp_count++;
					envp = malloc((envp_count + 1) * sizeof(char *));
					envp[envp_count] = malloc(ft_strlen(splited_prompt[count]) + 1 * sizeof(char *));
					ft_memcpy(envp[envp_count], splited_prompt[count], ft_strlen(splited_prompt[count]));
				}

			}
			else
				ft_putstr_fd("export: splited_pront[count]: not a valid identifier", 1);
            count++;
		}
			
            // Validar o que foi digitado
                // EXEMPLO: VAR=42 (tem que validar que VAR é um nome de variável válido)
            // Verificar se a variável existe no envp
                // Se não existir, adiciona no envp o que foi digitado (VAR=42)
                // Se existir... executa e dá uma olhada no que acontece

    }
}


size_t	ft_strlen_2(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '=')
		i++;
	return (i);
}


int valid_var(char **envp, char *var) //grep
{
	char	*value;
	int		len_var;
	int		i;

	i = 0;
	len_var = ft_strlen_2(var);
	while (envp[i] != NULL)
	{
		value = ft_strnstr (envp[i], var, len_var);
		if (value != NULL)
            return(1);
        else    
            return(0);
		i++;
	}
	return(1);
}

int localize_envp(char **envp, char *var) //grep
{
	char	*value;
	int		len_var;
	int		i;

	i = 0;
	len_var = ft_strlen_2(var);
	while (envp[i] != NULL)
	{
		value = ft_strnstr (envp[i], var, len_var);
		if (value != NULL)
            return(i);
		i++;
	}
	return(i);
}
