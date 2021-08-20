#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>

int	print_struct(t_command *st);

void	free_command(t_command *st)
{
	int i;

	i = 0;
	if (st->bin)
		free(st->bin);
	if (st->av)
	{
		while(st->av[i])
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
	printf("\b \n");
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

int main(int ac, char **av, char **env)
{
	char 		*str;
	t_command	*command;

	//add_history("export A=aaa"); //TEMP
	env = tabdup(env);
	str = " ";
	while (str)
	{
		signal(SIGINT, sig_m);
		rl_on_new_line();
		str = readline("\033[1;31m(っ•́｡•́)♪♬ \033[1;32m>\033[0;37m "/*">"*/);
		if (str && str[0])
		{
	//		add_history(str);
			command = parser(str, env);
			//printf("COMMAND OK\n");
			//print_struct(command);
			free(str);
			if (str[0])
				env = recurs_pipe(command, NULL, 0, env);
			free_command(command);
		}
	}
}