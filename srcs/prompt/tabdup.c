#include "minishell.h"

int tablen(char **tab)
{
	int i;

	i = 0;
	if (!tab || !tab[0])
		return (0);
	while(tab[i])
	{
		i++;
	}
	return (i);
}

char	**tabdup(char **tab)
{
	char **cpy;
	int i;

	i = 0;
	cpy = malloc(sizeof(char *) * tablen(tab));
	while(tab[i])
	{
		cpy[i] = ft_strdup(tab[i]);
		i++;
	}
	return (cpy);
}