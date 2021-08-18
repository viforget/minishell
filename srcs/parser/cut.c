/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 05:32:28 by lobertin          #+#    #+#             */
/*   Updated: 2021/08/11 19:31:51 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut(char *text)
{
	char	*final;
	int		x;
	int		y;
	int		z;
	int		i;

	x = 0;
	while (text[x] == ' ' || text[x] == '|')
		x++;
	y = 0;
	z = x;
	while (text[x])
	{
		y++;
		x++;
	}
	final = malloc(sizeof(char) * y + 1);
	i = 0;
	while (y--)
		final[i++] = text[z++];
	final[i] = '\0';
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
	while (text[x] == ' ' || text[x] == '|')
		x++;
	z = x;
	while (text[x++])
		y++;
	final = malloc(sizeof(char) * y + 1);
	x = 0;
	while ((y-- && text[z] != ' ') || guil == -1)
	{
		if (text[z] != 34)
			final[x++] = text[z++];
		else
		{
			z++;
			guil = guil * -1;
		}
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
	while (txt[pos] == ' ')
		pos++;
	while (txt[pos] && txt[pos] != ' ' && txt[pos] != '|')
	{
		if (txt[pos] == 34)
			pos++;
		final[posf] = txt[pos];
		pos++;
		posf++;
	}
	final[posf] = '\0';
	return (final);
}
