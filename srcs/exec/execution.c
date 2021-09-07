#include "minishell.h"

void	select_index(t_command *ins, char **env)
{
	if (ins->index == 0)
		execve(ins->bin, ins->av, env);
	else if (ins->index == 1)
		bi_echo(ins->av);
	else if (ins->index == 2)
		bi_pwd();
	else if (ins->index == 3)
		bi_env(env);
	exit(0);
}
