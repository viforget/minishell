#include "minishell.h"

int		len_name(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int 	check_in_env(char *str, char **env)
{
	int sz;
	int i;

	i = 0;
	sz = len_name(str);
	while (env[i])
	{
		if (memcmp(env[i], str, sz + 1) == 0)
		{
			printf("BALISE 2\n");
			return (i);
		}
		printf("BALISE\n");
		i++;
	}
	printf("BALISE 3\n");
	return (-1);
}

char	**ad_arg(char **env, char *str)
{
	char	**env2;
	int		i;

	printf("lolol\n");
	i = check_in_env(str, env);
	printf("lilil\n");
	if (i != -1)
	{
		printf("AAAA\n");
		free (env[i]);
		env[i] = str;
		return (env);
	}
	else
	{
		printf("BBBB\n");
		env2 = malloc(sizeof(char *) * tablen(env) + 1);
		while(env[i] && env[i + 1])
		{
			env2[i] = env[i];
			i++;
		}
		env2[i] = str;
		env2[i + 1] = env[i];
		bi_env(env);
		printf("----------\n");
		bi_env(env2);
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
	printf("aaa\n");
	while(av[i])
	{
		printf("str : %s\n", av[i]);
		env = ad_arg(env, av[i]);
		i++;
	}
	return (env);
}