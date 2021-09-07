#include "minishell.h"

void	free_command(t_command *st)
{
	int	i;

	i = 0;
	if (st->bin)
		free(st->bin);
	if (st->av)
	{
		while (st->av[i])
			free(st->av[i++]);
		free(st->av);
	}
	if (st->file)
		free(st->file);
	if (st->file_g)
		free(st->file_g);
}

void	sig_m(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		printf("\033[1;31m(っ•́｡•́)♪♬ \033[1;32m>\033[0;37m   \b\b");
}

char	*new_line(void)
{
	signal(SIGINT, sig_m);
	signal(SIGQUIT, sig_m);
	rl_on_new_line();
	return (readline("\033[1;31m(っ•́｡•́)♪♬ \033[1;32m>\033[0;37m "));
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	t_command	*command;

	env = tabdup(env);
	str = " ";
	while (str)
	{
		str = new_line();
		if (str && str[0])
		{
			add_history(str);
			if (str[0])
			{
				command = parser(str, env);
				free(str);
				env = recurs_pipe(command, NULL, 0, env);
			}
			else
				free(str);
			free_command(command);
		}
	}
	rl_clear_history();
	free_env(env);
	printf("exit\n");
}
