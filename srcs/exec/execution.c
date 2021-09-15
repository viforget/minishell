#include "minishell.h"

void	sig_p(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("QUIT: 3");
		kill(g_glob.fk, SIGKILL);
		g_glob.exit = 131;
	}
	else
		g_glob.exit = 130;
	printf("\n");
}

void	signal_p_set(int fk)
{
	g_glob.fk = fk;
	signal(SIGINT, sig_p);
	signal(SIGQUIT, sig_p);
}
