/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   av.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 05:36:24 by lobertin          #+#    #+#             */
/*   Updated: 2021/09/02 18:26:55 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_if(char x, char y, int test)
{
	if (test == 0)
	{
		if (x && (x != ' ' || ((y == '<' || y == '>') && x == ' ')))
			return (0);
	}
	if (test == 1)
	{
//		if (???)
			return (0);
	}
	return (1);
}

void	size_av(t_command *info, char *order, int size)
{
	int	pos;
	int	x;
	int	y;
	int	save;
	int	g;

	y = 0;
	pos = 0;
	printf("\n%s\n",order);
	while (order[pos] != '|' && order[pos] && size--)
	{
		x = 0;
		g = 0;
		while ((order[pos] == '|' || order[pos] == ' ' || order[pos] == '<'
				|| order[pos] == '>') && order[pos])
		{
			if (order[pos] == '<' || order[pos] == '>')
				while (ft_if(order[pos], order[pos - 1], 0) == 0)
					pos++;
			else
				pos++;
		}
		while (order[pos] != '|' && order[pos] != ' ' && order[pos] != '<'
			&& order[pos] != '>' && order[pos] != '\0')
		{
			if (order[pos] == 34)
			{
				g = 2;
				pos++;
				while (order[pos] != 34 && order[pos++])
					x++;
			}
			else
				x++;
			pos++;
		}
		save = pos - x - g;
		info->av[y] = malloc(sizeof(char *) * x + 1);
		remplir(info->av[y], order + save, x);
		y++;
	}
	info->av[y] = NULL;
}

void	nb_av(t_command *maillon, char *order)
{
	int	pos;
	int	x;
	int	save;

	pos = 0;
	save = 0;
	x = 0;
	while (order[pos])
	{
		while (order[pos] != '|' && order[pos])
		{
			while (order[pos] != ' ' && order[pos] != '<' && order[pos] != '>'
				&& order[pos] && order[pos] != '|')
			{
				if (order[pos] == 34)
				{
					pos++;
					while (order[pos] != 34)
						pos++;
				}
				pos++;
			}
			x++;
			while ((order[pos] == ' ' || order[pos] == '<' || order[pos] == '>')
				&& order[pos])
				pos++;
		}
		save = pos - save;
		maillon->av = malloc(sizeof(char *) * x + 1);
		size_av(maillon, cut(order + (pos - save)), x);
		while ((order[pos] == ' ' || order[pos] == '<' || order[pos] == '>'
			|| order[pos] == '|') && order[pos])
		{
			pos++;
		}
		maillon = maillon->next;
		x = 0;
	}
}
