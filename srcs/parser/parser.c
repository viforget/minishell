/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 19:12:45 by lobertin          #+#    #+#             */
/*   Updated: 2021/09/07 14:07:53 by lobertin         ###   ########.fr       */
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
		if ((order[pos] == ' ' || order[pos] == 9) && info->index == -1)
			info = set_bin(cutb(text), env, info);
		else if (order[pos] == '|' && order[pos + 1])
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

int	file_with_g_exit(char *order)
{
	int		i;
	char	*str;

	i = g_exit;
	str = ft_itoa(i);
	i = 0;
	while (str[i])
	{
		order[i] = str[i];
		i++;
	}
	return (strlen(str));
}

void	file_new(char *new, char *order, char **env, int s)
{
	int	x;
	int	y;
	int	e;

	x = 0;
	y = 0;
	while (x < s)
	{
		if (order[x] == 36)
		{
			if (order[x + 1] == 63)
			{
				y = y + file_with_g_exit(new + y);
				x = x + 2;
			}
			else if (find_env(env, next_word(order + x) + 1) != -1)
			{
				e = 0;
				while (env[find_env(env, next_word(order + x) + 1)][e] != 61)
					e++;
				e++;
				while (env[find_env(env, next_word(order + x) + 1)][e])
				{
					new[y] = env[find_env(env, next_word(order + x) + 1)][e];
					e++;
					y++;
				}	
				while (order[x] != 32 && order[x] != 124 && order[x] != 60
					&& order[x] != 62 && order[x] != 9)
					x++;
			}
			else
				while (order[x] != 32 && order[x] != 124 && order[x] != 60
					&& order[x] != 62 && order[x] != 9)
					x++;
		}
		else
		{
			new[y] = order[x];
			y++;
			x++;
		}
	}
	new[y] = '\0';
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
			if (order[pos + 1] == '?')
			{
				s = s + ft_ctoa(g_exit);
				pos++;
			}
			else if (find_env(ev, next_word(order + pos) + 1) != -1)
			{
				s = s + size_arg(ev, find_env(ev, next_word(order + pos) + 1));
				while (order[pos] != 32 && order[pos] != 124 && order[pos] != 60
					&& order[pos] != 62 && order[pos] && order[pos] != 9)
				{
					pos++;
					s--;
				}
			}
			else
				pos++;
		}
		else
		{
			s++;
			pos++;
		}
	}
	new = malloc(s + 1);
	file_new(new, order, ev, s + 1);
	return (new);
}

t_command	*parser(char *order, char **env)
{
	t_command	*info;

	info = mal_maillon();
	order = change_arg(order, env);
	order = verif_guil(order);
	if (order[0] < 32 && order[0] != 9)
		return (info);
	boucle(order, env, info);
	nb_av(info, order);
	clean(info);
	print_struct(info);
	return (info);
}
