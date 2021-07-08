#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>

int	print_struct(t_command *st);

int main(int ac, char **av, char **env)
{
	char *str;
	t_command *command;

	//printf("%d\n", ft_strlen("\033[0;31m(っ•́｡•́)♪♬\033[1;32m>\033[0;37m "));
	add_history("pwd | echo");
	while (1)
	{
		rl_on_new_line();
		str = readline("\033[1;31m(っ•́｡•́)♪♬ \033[1;32m>\033[0;37m ");
		add_history(str);
		command = parser(str, env);

		printf("COMMAND OK\n");
		print_struct(command);
		recurs_pipe(command, NULL, 0, env);
	}
}