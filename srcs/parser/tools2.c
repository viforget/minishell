/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 20:09:06 by lobertin          #+#    #+#             */
/*   Updated: 2021/09/02 17:07:14 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*next_word(char *order)
{
	char	*next_word;
	int		size;
	int		x;

	size = 0;
	x = 0;
	while (order[x] != 32 && order[x] != 124 && order[x] != 60 && order[x] != 62
		&& order[x])
	{
		x++;
		size++;
	}
	next_word = malloc(size + 1);
	size--;
	while (size >= 0)
	{
		next_word[size] = order[size];
		size--;
	}
	return (next_word);
}

int	size_arg(char **env, int pos)
{
	int	size;
	int	x;

	x = 0;
	while (env[pos][x] != '=')
		x++;
	size = 0;
	while (env[pos][x])
	{
		x++;
		size++;
	}
	return (size);
}

void	setg(t_command *info, char *order, int pos)
{
	if (order[pos] == '>' && order[pos + 1] == '>')
		set_guil(3, info, order, pos);
	else if (order[pos] == '>' && order[pos - 1] != '>')
		set_guil(2, info, order, pos);
	else if (order[pos] == '<')
		set_guil(1, info, order, pos);
}

int	ft_ctoa(unsigned char c)
{
	if (c < 10)
		return(1);
	if (c < 100)
		return(2);
	return(3);
}
