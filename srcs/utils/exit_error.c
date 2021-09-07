#include "minishell.h"

int	exit_error(char *exe, char *msg, int exit_value, int arg)
{
	if (arg == 0)
		printf("minishell: %s: %s\n", exe, msg);
	else if (arg == 4)
		printf("minishell: cd: %s: %s\n", exe, msg);
	else if (arg == 7)
		printf("minishell: exit: %s: %s\n", exe, msg);
	return (exit_value);
}
