char *put_expand(char **envp, char  *splited _prompt)
{
	int     count;
	int 	var_count
	char    *var;
	char	*result;

		while(splited_promp[count] != '\0')
		{
			if(splited_promp[count] == '$')
			{
				i++;
				if(splited_promp[count] == ' ')
					i++;
				else
				{
					while(splited_promp[count] != ' ' &&  splited_promp[count][i] != '\0')
					{
						var[var_count] = splited_promp[count];
						var_coount++;
						count++;
					}
				}
			}
		}
		result = ft_strdup( return_value(envp, var));
		return(result);
}

/*TO DO
strlen da linha completa -
strlen do nome da variavel $var +
strlen do valor da variavel

mallocar novo tamanho
copiar caracter por caracter até $(andar até o espaço)
copiar valor da $var
voltar pra pra pegar o resto da string
*/

char	*put_expand_quotes(char *prompt_line, char **envp)
{
	int     count;
	char    *var;
	int     count_var;
	int     size_var;
	char 	*result;

	count = 0;
	while(prompt_line[count] != '\0')
	{
		if(prompt_line[count] == '$')
		{
			count++;
			while(sprompt_line[count] != ' ' &&  prompt_line[count] != '\0')
			{
				var[count_var] = splited_promp[count];
				count_var++;
				count++;
			}
			count_var = ft_strlen(promp_line) - count_var;
			count_var--;
			size_var = ft_strlen(return_value(envp, var));
			size_var = size_var + count_var;
			result = malloc((size_var + 1) * sizeof(char *));
			var = resturn_value(envp, var);
			

		}
		count++;
	}
}


char *expand_var(char **envp, char *splited_promp)
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

				splited_prompt[count] = put_expand_quotes(splited_prompt[count], envp);
			}
			else if(splited_prompt[count][0] == '$')
			{	
				free(splited_promp[count]);
				splited_prompt[count] = put_expand(splited_prompt[count], envp);
			}
		}
	}
}
