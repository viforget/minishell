/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:17:47 by lobertin          #+#    #+#             */
/*   Updated: 2021/09/15 15:35:33 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*boucle(char *order, char **env, t_command *info)
{
	int			x[2];
	char		text[1000];

	x[0] = 0;
	x[1] = 0;
	while (order[x[1]])
	{
		text[x[0]] = order[x[1]];
		text[x[0] + 1] = '\0';
		if (order[x[1]] == 34 || order[x[1]] == 39)
			skip_guill_boucle(x, order, text, order[x[1]]);
		if ((order[x[1]] == ' ' || order[x[1]] == 9) && info->index == -1)
			info = set_bin(cutb(text), env, info);
		else if (order[x[1]] == '|' && order[x[1] + 1])
		{
			if (info->index == -1)
				set_bin(cutb(text), env, info);
			x[0] = new_list(&info, text, x, order);
		}
		for_norm(info, order, x);
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
		if (order[x[0]] == 39)
		{
			new[x[1]++] = order[x[0]++];
			while (order[x[0]] != 39)
				new[x[1]++] = order[x[0]++];
			new[x[1]++] = order[x[0]++];
		}
		else if (order[x[0]] == 36)
		{
			loop_norm(order, new, x, env);
		}
		else
			new[x[1] - 1] = ft_egal(order, x);
	}
	new[x[1]] = '\0';
}

void	ft_condition(char *order, int *pos, int *s, char **ev)
{
	char	*str;

	str = next_word(order + *pos);
	if (order[*pos + 1] == '?')
	{
		*s = *s + ft_ctoa(g_glob.exit);
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
		if (order[pos] == 39)
			loop_ch_arg(&pos, &s, order);
		else if (order[pos] == '$' && order[pos + 1])
			ft_condition(order, &pos, &s, ev);
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

	if (order[0] == '\t')
		order[0] = ' ';
	info = mal_maillon();
	order = change_arg(order, env);
	order = verif_guil(order);
	if (!(order) || order[0] < 32 || order[0] == 9)
		return (info);
	boucle(order, env, info);
	nb_av(info, order);
	clean(info);
	info = binfinal(info);
	free(order);
	return (info);
}
