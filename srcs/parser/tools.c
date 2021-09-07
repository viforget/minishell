/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 06:09:07 by lobertin          #+#    #+#             */
/*   Updated: 2021/09/06 16:07:06 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_char(char *c, char *test)
{
	int	x;
	int	i;
	int	j;

	x = 0;
	j = 0;
	while (c[j] && x == 0)
	{
		i = 0;
		while (x == 0 && test[i])
		{
			if (test[i] == c[j])
				x++;
			else
				i++;
		}
		j++;
	}
	return (x);
}

t_command	*mal_maillon(void)
{
	t_command	*info;

	info = malloc(sizeof(t_command));
	info->index = -1;
	info->bin = NULL;
	info->av = NULL;
	info->pipe = 0;
	info->guil = 0;
	info->file = NULL;
	info->file_g = NULL;
	info->next = NULL;
	return (info);
}

void	clean(t_command *info)
{
	int	x;

	while (info)
	{
		x = 0;
		while (info->av[x])
		{
			if (info->av[x][0] < 32)
				info->av[x] = NULL;
			x++;
		}
		info = info->next;
	}
}

void	remplir(char *dest, char *txt, int x)
{
	char	*send;
	int		y;
	int		z;

	y = 0;
	z = 0;
	while (z < x)
	{
		if (txt[y] != 34)
		{
			dest[z] = txt[y];
			z++;
		}
		y++;
	}
	dest[z] = '\0';
}

void	set_guil(int i, t_command *info, char *order, int pos)
{
	if (i == 1)
	{
		info->guil = 1;
		info->file_g = cutg(order + pos + 1);
	}
	if (i == 2)
	{
		info->pipe = 2;
		info->file = cutg(order + pos + 1);
	}
	if (i == 3)
	{
		info->pipe = 3;
		info->file = cutg(order + pos + 2);
	}
}
