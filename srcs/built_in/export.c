#include "minishell.h"

int	len_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

int	check_in_env(char *str, char **env)
{
	int	sz;
	int	i;

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

char	**minus_one(char **env, int i, char *str)
{
	free (env[i]);
	env[i] = ft_strdup(str);
	return (env);
}

char	**ad_arg_exp(char **env, char *str)
{
	char	**env2;
	int		i;

	i = check_in_env(str, env);
	if (i == -2)
		return (env);
	if (i != -1)
		return (minus_one(env, i, str));
	else
	{
		i = 0;
		env2 = malloc(sizeof(char *) * (tablen(env) + 2));
		while (env[i])
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
	int	i;

	i = 0;
	if (!av[0])
		bi_env(env);
	while (av[i])
	{
		env = ad_arg_exp(env, av[i]);
		i++;
	}
	return (env);
}
