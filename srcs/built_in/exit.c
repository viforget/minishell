#include "minishell.h"

void	bi_exit(t_command *ins, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	free_command(ins);
	printf("exit\n");
	exit(0);
}