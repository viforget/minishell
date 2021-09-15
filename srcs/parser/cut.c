/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 05:32:28 by lobertin          #+#    #+#             */
/*   Updated: 2021/09/15 10:26:52 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut(char *text)
{
	char	*final;
	int		x;
	int		y;
	int		z;

	x = 0;
	while ((text[x] == ' ' || text[x] == 9 || text[x] == '|') && text[x])
		x++;
	y = 0;
	z = x;
	while (text[x])
	{
		y++;
		x++;
	}
	final = malloc(sizeof(char) * y + 1);
	x = 0;
	while (y--)
		final[x++] = text[z++];
	final[x] = '\0';
	return (final);
}

char	*cutg(char *text)
{
	char	*final;
	int		x;
	int		y;
	int		z;
	int		guil;

	guil = 1;
	x = 0;
	y = 0;
	while (text[x] == ' ' || text[x] == 9 || text[x] == '|')
		x++;
	z = x;
	final = malloc(sizeof(char) * y + 1);
	x = 0;
	while (ft_if(text[z], text[z - 1], 1) || guil == -1)
	{
		if (text[z] != 34 || text[z] != 39)
			final[x++] = text[z];
		else
			guil = guil * -1;
		z++;
	}
	final[x] = '\0';
	return (final);
}

char	*cutb(char *txt)
{
	char	*final;
	int		pos;
	int		posf;

	final = malloc(8);
	pos = 0;
	posf = 0;
	while (txt[pos] == ' ' || txt[pos] == 9)
		pos++;
	while (ft_if(txt[pos], txt[pos + 1], 1) == 1)
	{
		if (txt[pos] == 34 || txt[pos] == 39)
			pos++;
		final[posf] = txt[pos];
		pos++;
		posf++;
	}
	final[posf] = '\0';
	return (final);
}
