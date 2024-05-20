#include "minishell.h"
/*****
	Testes
prompt = "     echo	 oi mundo"
prompt = "     echo	 oi mundo | ls"
prompt = "     echo	 oi mundo | ls              "
prompt = "     echo		\"oi		mundo\" | ls"
prompt = "     echo		\"oi		mundo\" | ls              "
prompt = " > file  echo	\"oi		mundo\" | ls  < other"
prompt = " > file  echo	\"oi		mundo\" | ls < other      "
prompt = " > file  echo	\"oi		mundo\" | ls < other | cat | echo << word > file"
prompt = " > file  echo	\"oi		mundo\" | ls < other | cat | echo << word > file    "
prompt = " > file  echo	\"oi		mundo\" | ls < other | cat | echo \"<< word >\" file    "
echo"oi"
echooi
*/

int     count_word(char *prompt)
{
    int	count; 
    int	word; 

    count = 0;
    word = 0;
    while (prompt[count] != '\0')
    {
        while (prompt[count] == ' ' || prompt == '\t')
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

char     *get_word(char *prompt)
{
    
}

char	**new_split(char *prompt)
{
	
}
