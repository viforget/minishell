#include "minishell.h"

int 	check_in_env_u(char *str, char **env)
{
	int sz;
	int i;

	i = 0;
	sz = len_name(str);
	while (env[i])
	{
		if (memcmp(env[i], str, sz) == 0 && env[i][sz] == '=')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

char	**supp_arg(char **env, char *str)
{
	int i;
	int j;
	int b;
	char **env2;

	b = 0;
	j = 0;
	i = check_in_env_u(str, env);
	printf("%s %d\n", str, i);
	if (i == -1)
		return (env);
	env2 = malloc(sizeof(char *) * tablen(env));
	while(env[j + b])
	{
			if (j == i)
				b = 1;
			env2[j] = env[j + b];
			j++;
	}
	env2[j] = NULL;
	free(env);
	return(env2);
}

char	**bi_unset(char **env, char **av)
{
	int i;

	i = 0;
	while(av[i])
	{

		env = supp_arg(env, av[i]);
		i++;
	}
	return (env);
}