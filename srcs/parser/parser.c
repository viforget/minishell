/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 19:12:45 by lobertin          #+#    #+#             */
/*   Updated: 2021/08/17 15:06:24 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_struct(t_command *st);

void	setg(t_command *info, char *order, int pos)
{
	if (order[pos] == '>' && order[pos + 1] == '>')
		set_guil(3, info, order, pos);
	else if (order[pos] == '>' && order[pos - 1] != '>')
		set_guil(2, info, order, pos);
	else if (order[pos] == '<')
		set_guil(1, info, order, pos);
}

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

t_command	*parser(char *order, char **env)
{
	t_command	*info;

	info = mal_maillon();
	if (order[0] < 32)
		return (info);
	boucle(order, env, info);
	nb_av(info, order);
	clean(info);
	return (info);
}
