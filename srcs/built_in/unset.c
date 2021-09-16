#include "minishell.h"

char	**supp_arg(char **env, char *str)
{
	int		i;
	int		j;
	int		b;
	char	**env2;

	b = 0;
	j = 0;
	i = find_env(env, str);
	if (i == -1)
		return (env);
	env2 = malloc(sizeof(char *) * tablen(env));
	while (env[j + b])
	{
		if (j == i)
		{
			free(env[j]);
			b = 1;
		}
		env2[j] = env[j + b];
		j++;
	}
	env2[j] = NULL;
	free(env);
	return (env2);
}

char	**bi_unset(char **env, char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		env = supp_arg(env, av[i]);
		i++;
	}
	return (env);
}
