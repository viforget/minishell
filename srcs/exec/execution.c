#include "minishell.h"

void	sig_p(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("QUIT: 3");
		kill(g_exit, SIGKILL);
		g_exit = 131;
	}
	else
		g_exit = 130;
	printf("\n");
}

void	signal_p_set(int fk)
{
	g_exit = fk;
	signal(SIGINT, sig_p);
	signal(SIGQUIT, sig_p);
}