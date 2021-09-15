/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:05:09 by lobertin          #+#    #+#             */
/*   Updated: 2021/09/14 17:31:56 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip(char *txt, char exmpl)
{
	int	pos;

	pos = 0;
	if (txt[pos] == exmpl)
	{
		pos++;
		while (txt[pos] != exmpl)
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
		else if (order[pos] == 39)
		{
			pos++;
			while (order[pos] != 39)
			{	
				pos++;
			}
		}
		pos++;
	}
	return (pos);
}

void	skip_new(char **env, char *order, char *new, int x[2])
{
	int		e;
	char	*s;

	e = 0;
	s = next_word(order + x[0]);
	while (env[find_env(env, s + 1)][e] != 61)
		e++;
	e++;
	while (env[find_env(env, s + 1)][e])
	{
		new[x[1]] = env[find_env(env, s + 1)][e];
		e++;
		x[1]++;
	}
	free(s);
	while (ft_if(order[x[0]], order[x[0] + 1], 1))
	{
		x[0]++;
		cond_loop(order, x, new);
	}
}

void	skip_guill_boucle(int x[2], char *order, char text[1000], char exp)
{
	x[1]++;
	x[0]++;
	while (order[x[1]] != exp && order[x[1]])
	{
		text[*x] = order[x[1]];
		text[*x + 1] = '\0';
		x[1]++;
		x[0]++;
	}
	x[1]++;
}
