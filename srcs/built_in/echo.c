#include "minishell.h"

int	bi_echo(char **av)
{
	int		i;
	char	n;

	n = 0;
	i = 1;
	if (av[1])
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			n = 1;
			i++;
		}
		while (av[i])
		{
			printf("%-*s", (int)ft_strlen(av[i]) + (av[i + 1] != 0), av[i]);
			i++;
		}
	}
	if (n == 0)
		printf("%c", '\n');
	g_exit = 0;
	return (1);
}
