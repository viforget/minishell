#include "minishell.h"

int main(int ac, char **av, char **env)
{
	char *str;

	while (get_next_line(1, &str))
		parser(str, env);
}