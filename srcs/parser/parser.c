/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 19:12:45 by lobertin          #+#    #+#             */
/*   Updated: 2021/08/30 15:28:28 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_struct(t_command *st);

t_command	*boucle(char *order, char **env, t_command *info)
{
	int			pos;
	int			x;
	char		text[1000];

	pos = 0;
	x = 0;
	while (order[pos])
	{
		text[x] = order[pos];
		text[x + 1] = '\0';
		if (order[pos] == 34)
		{
			pos++;
			x++;
			while (order[pos] != 34 && order[pos])
			{
				text[x] = order[pos];
				text[x + 1] = '\0';
				pos++;
				x++;
			}
			pos++;
		}
		if (order[pos] == ' ' && info->index == -1)
			info = set_bin(cutb(text), env, info);
		else if (order[pos] == '|')
		{
			if (info->index == -1)
				set_bin(cut(text), env, info);
			x = -1;
			if (info->pipe == 0)
				info->pipe = 1;
			info->next = mal_maillon();
			info = info->next;
			while (order[pos] == '|')
				pos++;
			pos--;
			text[0] = '\0';
		}
		setg(info, order, pos);
		pos++;
		x++;
	}
	if (info->index == -1)
		set_bin(cutb(text), env, info);
	return (info);
}

void	file_new(char *new, char *order, char **env)
{
	int	x;
	int	y;
	int	e;

	x = 0;
	y = 0;
	while (order[x])
	{
		if (order[x] == '$')
		{
			if (find_env(env, next_word(order + x) + 1) != -1)
			{
				e = 0;
				while (order[x] && env[find_env(env, next_word(order + x) + 1)][e] != '=')
					e++;
				e++;
				while (order[x] && env[find_env(env, next_word(order + x) + 1)][e])
				{
					new[y] = env[find_env(env, next_word(order + x) + 1)][e];
					e++;
					y++;
				}	
				while (order[x] != ' ')
					x++;
			}
			else
				while (order[x] != ' ')
					x++;
		}
/*		else if (order[x] == 39)
		{
			x++;
			while(order[x] != 39)
				x++;
			x++;
		}*/
		else
		{
			new[y] = order[x];
			y++;
			x++;
		}
	}
}

char	*change_arg(char *order, char **ev)
{
	int		pos;
	int		s;
	char	*new;

	pos = 0;
	s = 0;
	while (order[pos])
	{
		if (order[pos] == '$')
		{
			if (find_env(ev, next_word(order + pos) + 1) != -1)
			{
				s = s + size_arg(ev, find_env(ev, next_word(order + pos) + 1));
				while (order[pos] != ' ' && order[pos])
				{
					pos++;
					s--;
				}
			}
			else
				pos++;
		}
/*		else if (order[pos] == 39)
		{
			pos++;
			while(order[pos] != 39)
				pos++;
			pos++;
		}*/
		else
		{
			s++;
			pos++;
		}
	}
	new = malloc(s + 1);
	file_new(new, order, ev);
	return (new);
}

t_command	*parser(char *order, char **env)
{
	t_command	*info;

	info = mal_maillon();
	if (order[0] < 32)
		return (info);
	order = change_arg(order, env);
//	printf("[%s]\n", order);
	boucle(order, env, info);
	nb_av(info, order);
	clean(info);
	print_struct(info);
	return (info);
}
