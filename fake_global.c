// #include "minishell.h"
#include <stdio.h>

int	*func_test(void)
{
	static int var;
	return(&var);
}

int main(void)
{
	int *temp;

	temp = func_test();
	printf("%i\n", temp[0]);
	temp[0] = 4;
	printf("%i\n", temp[0]);
	return(0);
}