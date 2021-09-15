/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:35:06 by viforget          #+#    #+#             */
/*   Updated: 2021/09/15 15:35:18 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_norm(char *order, char *new, int x[2], char **env)
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
		if (ft_if(order[x[0] + 1], order[x[0]], 2))
			new[x[1]++] = order[x[0]];
		while (ft_if(order[x[0]], order[x[0] + 1], 1))
			x[0]++;
	}
}

void	loop_ch_arg(int *pos, int *s, char *order)
{
	(*pos)++;
	(*s)++;
	while (order[*pos] != 39)
	{
		(*s)++;
		(*pos)++;
	}
	(*s)++;
	(*pos)++;
}
