#include "minishell.h"
#include <fcntl.h>

#include <stdio.h>

void	double_close(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	cond_dup_close(int fd, int fd2, int nb)
{
		dup2(fd, nb);
		close(fd);
		if (fd2 != -1)
			close(fd2);
}

void	sig_p(int sig)
{
	printf("\b\b  \b\b");
	exit(0);
}

char	**exec_built_in(t_command *ins, char **av, char **env)
{
	printf("%d\n", ins->index);
	if (ins->index == 1)
		bi_echo(av);
	//if (ins->index == 2)
	//	bi_pwd(env);
	if (ins->index == 3)
		bi_env(env);
	if (ins->index == 5)
		env = bi_export(env, av + 1);
	return (env);
}

void	recurs_pipe(t_command *ins, int fd_p[2], int pip, char **env)
{
	int fk;
	int fd[2];
	int fd_n[2];

	if (ins->pipe == 1)
		pipe(fd_n);
	if (ins->pipe == 2)
	{
		fd[0] = open(ins->file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	if (ins->pipe == 3)
	{
		fd[0] = open(ins->file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	if (ins->guil == 1)
	{
		fd[1] = open(ins->file_g, O_RDONLY | O_APPEND);
	}
	

	if (ins->index != 0)
			env = exec_built_in(ins, ins->av, env);
	else
	{	
		fk = fork();
		if (fk == 0)
		{
			if(pip == 1)
			{
				cond_dup_close(fd_p[0], fd_p[1], 0);
			}
			if(ins->pipe == 1)
			{
				cond_dup_close(fd_n[1], fd_n[0], 1);
			}
			if (ins->pipe == 2 || ins->pipe == 3)
			{
				cond_dup_close(fd[0], -1, 1);
			}
			if (ins->guil == 1)
			{
				cond_dup_close(fd[1], -1, 0);
			}
			if (ins->index == 0)
				execve(ins->bin, ins->av, env);
			exit(0);
		}
		else
		{
			signal(SIGINT, sig_p);
		}
	}
	if (ins->pipe >= 2 && ins->pipe <= 3)
		close(fd[0]);
	if (ins->guil == 1)
		close(fd[1]);
	if(pip == 1)
		double_close(fd_p);
	if (/*ins->pipe == 1 && */ins->next)
	{
		recurs_pipe(ins->next, fd_n, ins->pipe, env);
	}
	if(ins->pipe == 1)
		double_close(fd_n);
	if (ins->index == 0)
		waitpid(fk, NULL, 0);
}