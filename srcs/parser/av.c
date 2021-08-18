/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   av.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 05:36:24 by lobertin          #+#    #+#             */
/*   Updated: 2021/08/17 17:32:54 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	size_av(t_command *info, char *order, int size)
{
	int	pos;
	int	x;
	int	y;
	int	save;
	int	g;

	y = 0;
	pos = 0;
	while (order[pos] != '|' && order[pos] && size--)
	{
		x = 0;
		g = 0;
		while (order[pos] == '|' || order[pos] == ' ' || order[pos] == '<'
			|| order[pos] == '>')
		{
			if (order[pos] == '<' || order[pos] == '>')
				while (order[pos] != ' ' || ((order[pos - 1] == '<' || order[pos - 1] == '>') && order[pos] == ' '))
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
				while (order[pos] != 34)
				{
					pos++;
					x++;
				}
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
		while (order[pos] == ' ' || order[pos] == '<' || order[pos] == '>'
			|| order[pos] == '|')
			pos++;
		maillon = maillon->next;
		x = 0;
	}
}
