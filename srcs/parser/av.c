/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   av.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 05:36:24 by lobertin          #+#    #+#             */
/*   Updated: 2021/09/13 15:00:34 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_if(char x, char y, int test)
{
	if (test == 0)
	{
		if (x && (x != ' ' || x != 9 || ((y == '<' || y == '>') && x == ' ')))
			return (1);
	}
	if (test == 1)
	{
		if (x != 32 && x != 124 && x != 60 && x != 62 && x != 9 && x)
			return (1);
	}
	return (0);
}

int	skip_av(char *order, int *pos, int *x)
{
	int	g;

	*x = 0;
	g = 0;
	*pos = *pos + skip_hard(order + *pos);
	while (ft_if(order[*pos], order[*pos - 1], 1))
	{
		if (order[*pos] == 34)
		{
			g = 2;
			(*pos)++;
			while (order[*pos] != 34 && order[(*pos)++])
			{	
				*x = *x + 1;
			}
		}
		else
			*x += 1;
		(*pos)++;
	}
	return (*pos - *x - g);
}

void	size_av(t_command *info, char *order, int size)
{
	int	pos;
	int	x;
	int	y;
	int	save;

	y = 0;
	pos = 0;
	while (order[pos] != '|' && order[pos] && size--)
	{
		save = skip_av(order, &pos, &x);
		info->av[y] = malloc(sizeof(char *) * x + 1);
		remplir(info->av[y], order + save, x);
		y++;
	}
	info->av[y] = NULL;
}

int	nb_word(char *order)
{
	int	x;
	int	pos;

	x = 0;
	pos = 0;
	while (order[pos] == ' ' || order[pos] == 9)
		pos++;
	while (order[pos] != '|' && order[pos])
	{
		pos = skip_pos(order, pos);
		x++;
		while ((order[pos] == ' ' || order[pos] == 9
				|| order[pos] == '<' || order[pos] == '>') && order[pos])
		{
			if (order[pos] == '<' || order[pos] == '>')
				x--;
			pos++;
		}
	}
	return (x);
}

void	nb_av(t_command *maillon, char *order)
{
	int	pos;
	int	x;
	int	save;

	pos = 0;
	x = 0;
	while (order[pos])
	{
		x = nb_word(order + pos);
		maillon->av = malloc(sizeof(char *) * x + 1);
		size_av(maillon, cut(order + (pos)), x);
		while (order[pos] != '|' && order[pos])
		{
			if (order[pos] == 34)
				pos = pos + skip(order + pos);
			pos++;
		}
		while (order[pos] == '|' && order[pos])
			pos++;
		maillon = maillon->next;
		x = 0;
	}
}
