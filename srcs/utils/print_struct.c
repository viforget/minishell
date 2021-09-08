//
//PENSER A DELETE AVANT DE PUSH
//

#include "minishell.h"

void	print_struct(t_command *st)
{
	int	i;
	i = 0;
	printf("index  : %d\n", st->index);
	if (st->bin)
		printf("bin    : |%s|\n", st->bin);
	else
		printf("bin    : NULL\n");
	if (st->av)
	{
		while(st->av[i])
		{
			printf("av[%i]  : |%s|\n", i, st->av[i]);
			i++;
		}
	}
	else
		printf("av     : NULL\n");
	printf("pipe   : %d\n", st->pipe);
	printf("guil   : %d\n", st->guil);
	if (st->file)
		printf("file   : |%s|\n", st->file);
	else
		printf("file   : NULL\n");
	if (st->file_g)
		printf("file_g : |%s|\n", st->file_g);
	else
		printf("file_g : NULL\n");
	if (st->next)
	{	
		printf("next   : %p\n\n", st->next);
		print_struct(st->next);
	}
	else
		printf("next   : NULL\n");	
}
