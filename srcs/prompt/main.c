#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>

int	print_struct(t_command *st);

void	sig_m(int sig)
{
	printf("\b \n");
	rl_on_new_line();
	rl_line_buffer = "\033[1;31m(っ•́｡•́)♪♬ \033[1;32m>\033[0;37m ";
	rl_redisplay();
}

int main(int ac, char **av, char **env)
{
	char 		*str;
	t_command	*command;

	add_history("export A=aaa"); //TEMP
	env = tabdup(env);
	while (1)
	{
		signal(SIGINT, sig_m);
		rl_on_new_line();
		str = readline("\033[1;31m(っ•́｡•́)♪♬ \033[1;32m>\033[0;37m "/*">"*/);
		if (str[0])
		{
			add_history(str);
			command = parser(str, env);
			printf("COMMAND OK\n");
			recurs_pipe(command, NULL, 0, env);
		}
	}
}