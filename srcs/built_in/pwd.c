#include "minishell.h"

void	bi_pwd()
{
	char *str;

	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
}