/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:05:09 by lobertin          #+#    #+#             */
/*   Updated: 2021/09/10 09:50:27 by viforget         ###   ########.fr       */
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

char	*executable(char *order, t_command *info)
{
	int		size;
	int		pos;
	char	*path;

	printf("%s\n", order);
	size = 0;
	while (order[size] != 32 && order[size])
		size++;
	path = malloc(sizeof(char) * size);
	pos = -1;
	while (++pos < size)
		path[pos] = order[pos];
	path[pos] = '\0';
	info->index = 0;
	return (path);
}
