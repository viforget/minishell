/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:05:09 by lobertin          #+#    #+#             */
/*   Updated: 2021/09/10 19:49:51 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip(char *txt)
{
	int	pos;

	pos = 0;
	if (txt[pos] == 34)
	{
		pos++;
		while (txt[pos] != 34)
			pos++;
	}
	return (pos);
}

int	skip_hard(char *order)
{
	int	pos;

	pos = 0;
	while ((order[pos] == '|' || order[pos] == ' ' || order[pos] == 9
			|| order[pos] == '<' || order[pos] == '>') && order[pos])
	{
		if (order[pos] == '<' || order[pos] == '>')
		{
			while ((order[pos] == '|' || order[pos] == ' ' || order[pos] == 9
					|| order[pos] == '<' || order[pos] == '>') && order[pos])
				pos++;
			while (ft_isalnum(order[pos]))
				pos++;
		}
		else
			pos++;
	}
	return (pos);
}

int	skip_pos(char *order, int pos)
{
	while (ft_if(order[pos], order[pos + 1], 1))
	{
		if (order[pos] == 34)
		{
			pos++;
			while (order[pos] != 34)
				pos++;
		}
		pos++;
	}
	return (pos);
}

void	skip_new(char **env, char *order, char *new, int x[2])
{
	int	e;

	e = 0;
	while (env[find_env(env, next_word(order + x[0]) + 1)][e] != 61)
		e++;
	e++;
	while (env[find_env(env, next_word(order + x[0]) + 1)][e])
	{
		new[x[1]] = env[find_env(env, next_word(order + x[0]) + 1)][e];
		e++;
		x[1]++;
	}
	while (ft_if(order[x[0]], order[x[0] + 1], 1))
	{
		x[0]++;
		if (ft_isalnum(order[x[0]]) == 0)
		{
			while (ft_if(order[x[0]], order[x[0] + 1], 1))
			{
				new[x[1]] = order[x[0]];
				x[0]++;
				x[1]++;
			}
		}
	}
}

void	skip_guil_boucle(int *pos, int *x, char *order, char text[1000])
{
	(*pos)++;
	(*x)++;
	while (order[*pos] != 34 && order[*pos])
	{
		text[*x] = order[*pos];
		text[*x + 1] = '\0';
		(*pos)++;
		(*x)++;
	}
	(*pos)++;
}
