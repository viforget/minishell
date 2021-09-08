#include "minishell.h"

void	sig_p(int sig)
{
	printf("\b\b  \b\b");
	exit(0);
}

char	**exec_built_in(t_command *ins, char **av, char **env)
{
	g_exit = 0;
	if (ins->index == 1)
		bi_echo(av);
	if (ins->index == 2)
		bi_pwd();
	if (ins->index == 3)
		bi_env(env);
	if (ins->index == 4)
		bi_cd(av[1], env);
	if (ins->index == 5)
		env = bi_export(env, av + 1);
	if (ins->index == 6)
		env = bi_unset(env, av + 1);
	if (ins->index == 7)
		bi_exit(ins, env, av);
	return (env);
}

void	execution(t_command *ins, char **env)
{
	if (ins->index == 0)
	{
		execve(ins->bin, ins->av, env);
		g_exit = exit_error(ins->av[0], "command not found", 127, 0);
	}
	exec_built_in(ins, ins->av, env);
	free_command(ins);
	free_env(env);
	exit(0);
}

char	**end_recurs(t_command *ins, int fd_n[2], char **env, int fk)
{
	if (ins->next)
		recurs_pipe(ins->next, fd_n, ins->pipe, env);
	if (ins->pipe == 1)
		double_close(fd_n);
	if (ins->index <= 3 && ins->index > -1)
	{
		waitpid(fk, &g_exit, 0);
		g_exit = g_exit / 256;
	}
	return (env);
}

char	**recurs_pipe(t_command *ins, int fd_p[2], int pip, char **env)
{
	int	fk;
	int	fd[2];
	int	fd_n[2];

	pipe_and_open(fd_n, fd, ins);
	if (ins->index > 3)
		env = exec_built_in(ins, ins->av, env);
	else if (ins->index != -1)
	{	
		fk = fork();
		if (fk == 0)
		{
			if (pip == 1)
				cond_dup_close(fd_p[0], fd_p[1], 0);
			opcl_pipe(ins, fd_p, fd_n, fd);
			execution(ins, env);
		}
		else
			signal(SIGINT, sig_p);
	}
	else if (ins->av && ins->av[0])
		g_exit = exit_error(ins->av[0], "command not found", 127, 0);
	pipe_and_exit(ins, fd, fd_p, pip);
	return (end_recurs(ins, fd_n, env, fk));
}
