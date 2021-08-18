#include <stdio.h>
#include <stdlib.h>
size_t  ft_strlen(const char *str);
int     ft_strcmp(const char *s1, const char *s2);

int bi_echo(char **av)
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
		while(av[i])
		{
			printf("%-*s", (int)ft_strlen(av[i]) + (av[i + 1] != 0), av[i]);
			i++;	
		}
	}
	if (n == 0)
		printf("%c", '\n');
	return (1);
}