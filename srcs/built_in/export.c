#include "minishell.h"

int		len_name(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

int 	check_in_env(char *str, char **env)
{
	int sz;
	int i;

	i = 0;
	sz = len_name(str);
	if (sz == -1)
		return (-2);
	while (env[i])
	{
		if (memcmp(env[i], str, sz + 1) == 0)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

char	**ad_arg(char **env, char *str)
{
	char	**env2;
	int		i;

	i = check_in_env(str, env);
	if (i == -2)
		return (env);
	if (i != -1)
	{
		free (env[i]);
		env[i] = str;
		return (env);
	}
	else
	{
		env2 = malloc(sizeof(char *) * tablen(env) + 2);
		while(env[i])
		{
			env2[i] = env[i];
			i++;
		}
		env2[i] = ft_strdup(str);
		env2[i + 1] = NULL;
		free(env);
	}
	return (env2);
}

char	**bi_export(char **env, char **av)
{
	int i;

	i = 0;
	if (!av[0])
		bi_env(env);
	while(av[i])
	{
		env = ad_arg(env, av[i]);
		i++;
	}
	return (env);
}