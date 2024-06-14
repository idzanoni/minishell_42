#include "minishell.h"

/*TO DO
strlen da linha completa -
strlen do nome da variavel $var +
strlen do valor da variavel

mallocar novo tamanho
copiar caracter por caracter até $(andar até o espaço)
copiar valor da $var
voltar pra pra pegar o resto da string
*/


char *expand_var2(t_list *envp, char **splited_prompt)
{
	int count;

	count = 0;
	while (splited_prompt[count] != NULL)
	{
		if (ft_strchr(splited_prompt[count], '$') != NULL)
		{
			if(splited_prompt[count][0] == '\'')
				count++;
			else if(splited_prompt[count][0] == '"')
			{
				splited_prompt[count] = put_expand(envp, splited_prompt[count]);
			}
			else if(splited_prompt[count][0] == '$')
			{	
				splited_prompt[count] = put_expand(envp, splited_prompt[count]);
			}
		}
	}
	return(splited_prompt[count]);
}


char *put_expand(t_list *envp, char  *splited_promp)
{
	int     count;
	int 	var_count;
	char    *var;
	t_list  *tmp;
    char    *result;
	int		i;

		i = 0;
		var_count = 0;
		count = 0;
		result = malloc(16 * sizeof(char));
		var = malloc(6 * sizeof(char));
		while(splited_promp[count] != '\0')
		{
			if(splited_promp[count] == '$')
			{
				count++;
				if(splited_promp[count] == ' ')
					count++;
				else
				{
					while(splited_promp[count] != ' ' &&  splited_promp[count] != '\0')
					{
						var[var_count] = splited_promp[count];
						var_count++;
						count++;
					}
				}
			}
			else
				count++;
		}
		tmp = localize_envp(envp, var);
        count = 0;
        while(((char *)tmp->content)[i] != '\0')
		{
			if (((char *)tmp->content)[i] == '=')
			{
                i++;
                while(((char *)tmp->content)[i] != '\0')
                {
			    	result[count] = ((char *)envp->content)[i];
                    i++;
					count++;
                }		
			}
            i++;
        }
		result[count] = '\0';
		printf("%s", result);
		return(result);
}

