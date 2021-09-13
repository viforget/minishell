/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:17:47 by lobertin          #+#    #+#             */
/*   Updated: 2021/09/13 20:20:32 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			skip_guil_boucle(&pos, &x, order, text);
		if ((order[pos] == ' ' || order[pos] == 9) && info->index == -1)
			info = set_bin(cutb(text), env, info);
		else if (order[pos] == '|' && order[pos + 1])
		{
			if (info->index == -1)
				set_bin(cutb(text), env, info);
			x = new_list(&info, text, &pos, order);
		}
		for_norm(info, order, &pos, &x);
	}
	if (info->index == -1)
		set_bin(cutb(text), env, info);
	return (info);
}

void	file_new(char *new, char *order, char **env, int s)
{
	int	x[2];

	x[0] = 0;
	x[1] = 0;
	while (x[0] < s)
	{
		if (order[x[0]] == 36)
		{
			if (order[x[0] + 1] == 63)
			{
				x[1] = x[1] + file_with_g_exit(new + x[1]);
				x[0] = x[0] + 2;
			}
			else if (use_find(env, next_word(order + x[0])) != -1)
				skip_new(env, order, new, x);
			else
			{
				while (ft_if(order[x[0]], order[x[0] + 1], 1))
					x[0]++;
			}
		}
		else
			new[x[1] - 1] = ft_egal(order, x);
	}
	new[x[1]] = '\0';
}

void	ft_condition(char *order, int *pos, int *s, char **ev)
{
	char *str;

	str = next_word(order + *pos);
	if (order[*pos + 1] == '?')
	{
		*s = *s + ft_ctoa(g_exit);
		(*pos)++;
	}
	else if (find_env(ev, str + 1) != -1)
	{
		*s = *s + size_arg(ev, find_env(ev, str + 1));
		while (ft_isalnum(order[++(*pos)]))
			s--;
		(*pos)++;
	}
	else
		(*pos)++;
	free(str);
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
			ft_condition(order, &pos, &s, ev);
		}
		else
		{
			s++;
			pos++;
		}
	}
	new = malloc(s + 1);
	file_new(new, order, ev, s + 1);
	free(order);
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
	info = binfinal(info);
	free(order);
	return (info);
}
