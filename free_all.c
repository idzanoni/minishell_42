#include "minishell.h"

void	free_all(char **malloc_string)
{
	int	count;

	count = 0;
	if (!malloc_string)
		return ;
	while (malloc_string[count] != NULL)
	{
		free(malloc_string[count]);
		count++;
	}
	free(malloc_string);
}
