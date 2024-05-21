#include "minishell.h"
/*****
	Testes
prompt = "     echo	 oi mundo"
prompt = "     echo	 oi mundo | ls"
prompt = "     echo	 oi mundo | ls              "
prompt = "     echo		"oi		mundo" | ls"
prompt = "     echo		"oi		mundo" | ls              "
prompt = " > file  echo "oi     mundo" | ls  < other"
prompt = " > file  echo	"oi		mundo" | ls < other      "
prompt = " > file  echo	"oi		mundo" | ls < other | cat | echo << word > file"
prompt = " > file  echo	"oi		mundo" | ls < other | cat | echo << word > file    "
prompt = " > file  echo	"oi		mundo" | ls < other | cat | echo "<< word >" file    "
echo"oi"
echooi
*/

int	count_word(char *prompt)
{
	int	count; 
	int	word;
 

	count = 0;
	word = 0;
	while (prompt[count] != '\0')
	{
		while (prompt[count] == ' ' || prompt[count] == '\t')
			count++;
		if (prompt[count] == 34)
		{
			word++;
			while (prompt[count] != 34 && prompt[count] != '\0')
				count++;
		}
		else if (prompt[count] == 39)
		{
			word++;
			while (prompt[count] != 39 && prompt[count] != '\0')
				count++;
		}
		else if (prompt[count] != '\0')
			word++;
		while (prompt[count] != '\0' && prompt[count] != ' ' && prompt[count] != '\t')
			count++;
	}
	return (word);
}

char	*get_word(char *prompt, int *count)
{ 
	int		word;
    char	*word_splited;
	int		temp;
	
	word = 0;
	if (prompt[*count] == 34)
	{
		word = *count;
		(*count)++;
		while (prompt[*count] != 34 && prompt[*count] != '\0')
			*count = *count + 1;
		word = (*count + 1) - word;
		word_splited = malloc((word + 1) * sizeof(char *));
		if (!word_splited)
			return (NULL);
	}
	else if (prompt[*count] == 39)
	{
		word = *count;
		(*count)++;
		while (prompt[*count] != 39 && prompt[*count] != '\0')
			*count = *count + 1;
		word = (*count + 1) - word;
		word_splited = malloc((word + 1) * sizeof(char *));
		if (!word_splited)
			return (NULL);
	}
	else if (prompt[*count] != '\0')
	{
		word = *count;
		while (prompt[*count] != ' ' && prompt[*count] != '\t' && prompt[*count] != '\0')
			*count = *count + 1;
		word = (*count + 1) - word;
		word_splited = malloc((word + 1) * sizeof(char *));
		if (!word_splited)
			return (NULL);
	}
	word_splited[word--] = '\0';
	temp = *count;
	while (word >= 0)
		word_splited[word--] = prompt[temp--];
    return (word_splited);
}

char	**new_split(char *prompt)
{
	char	**splited_promp;
	int		word_number;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (!prompt)
		return (NULL);
	word_number = count_word(prompt);
	splited_promp = (char **)malloc((word_number + 1) * sizeof(char *));
	if (!splited_promp)
		return (NULL);
	while (prompt[count] != '\0')
	{
		while (prompt[count] == ' ' || prompt[count] == '\t')
			count++;
		if (prompt[count] != '\0')
		{
			splited_promp[i] = get_word(prompt, &count);
			if (splited_promp[i] == NULL)
			{
				free_all(splited_promp);
				return (NULL);
			}
			i++;
		}
		while (prompt[count] != ' ' && prompt[count] != '\t' && prompt[count] != '\0')
			count++;
	} 
	splited_promp[i] = NULL;
	return(splited_promp);  
}
