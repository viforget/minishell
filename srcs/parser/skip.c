/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:05:09 by lobertin          #+#    #+#             */
/*   Updated: 2021/09/07 19:08:30 by lobertin         ###   ########.fr       */
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
			while (ft_if(order[pos], order[pos - 1], 0) == 0)
				pos++;
		else
			pos++;
	}
	return (pos);
}
