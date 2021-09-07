#include "minishell.h"

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

void	opcl_pipe(t_command *ins, int fd_p[2], int fd_n[2], int fd[2])
{
	if (ins->pipe == 1)
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
}

void	pipe_and_open(int fd_n[2], int fd[2], t_command *ins)
{
	if (ins->pipe == 1)
		pipe(fd_n);
	if (ins->pipe == 2)
		fd[0] = open(ins->file, 513);
	if (ins->pipe == 3)
		fd[0] = open(ins->file, 521);
	if (ins->guil == 1)
		fd[1] = open(ins->file_g, O_RDONLY | O_APPEND);
}

void	pipe_and_exit(t_command *ins, int fd[2], int fd_p[2], int pip)
{
	if (pip == 1)
		double_close(fd_p);
	if (ins->pipe >= 2 && ins->pipe <= 3)
		close(fd[0]);
	if (ins->guil == 1)
		close(fd[1]);
}
