#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>


int main(int ac, char **av, char **env)
{
	char *str;

	//printf("%d\n", ft_strlen("\033[0;31m(っ•́｡•́)♪♬\033[1;32m>\033[0;37m "));
	while (/*write(1, "\033[1;31m(っ•́｡•́)♪♬ \033[1;32m>\033[0;37m ", 48) /*&& readline(str)*/1)
	{
		rl_on_new_line();
		str = readline("\033[1;31m(っ•́｡•́)♪♬ \033[1;32m>\033[0;37m ");
		add_history(str);
		printf("s: %s\n", str);
		parser(str, env);
	}
}