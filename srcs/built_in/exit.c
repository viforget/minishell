#include "minishell.h"

int	ft_atoc(const char *str)
{
	int					x;
	unsigned long long	n_final;
	int					negatif;

	n_final = 0;
	negatif = 1;
	x = 0;
	while ((str[x] <= 9 && str[x] >= 13 ) || str[x] == ' ')
		x++;
	if (str[x] == '-' || str[x] == '+')
	{
		if (str[x++] == '-')
			negatif = negatif * -1;
	}
	while (str[x] <= '9' && str[x] >= '0' && str[x])
	{
		n_final = n_final * 10 + (str[x++] - 48);
		if (n_final > 2147483648)
			return (-1);
	}
	if (str[x])
		return (-1);
	n_final = n_final * negatif;
	return ((unsigned char)n_final);
}

void	bi_exit(t_command *ins, char **env, char **av)
{
	int	i;
	int	ret;

	i = 0;
	printf("exit\n");
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	i = 0;
	ret = 0;
	if (av && av[1])
	{
		ret = ft_atoc(av[1]);
		if (ret == -1)
			printf("minishell: exit: %s: numeric argument required\n", av[1]);
	}
	free_command(ins);
	exit(ret);
}
