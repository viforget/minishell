/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fornorm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 20:04:19 by viforget          #+#    #+#             */
/*   Updated: 2021/09/14 15:14:36 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cond_loop(char *order, int x[2], char *new)
{
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

void	for_norm(t_command *info, char *order, int *pos, int *x)
{
	setg(info, order, *pos);
	(*pos)++;
	(*x)++;
}
