/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 19:12:38 by viforget          #+#    #+#             */
/*   Updated: 2021/09/10 20:04:16 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	ft_egal(char *order, int x[2])
{
	char	c;

	c = order[x[0]];
	x[0]++;
	x[1]++;
	return (c);
}

t_command	*binfinal(t_command *info)
{
	if (info->index == -1 && info->av)
	{
		info->index = 0;
		info->bin = ft_strdup(info->av[0]);
	}
	if (info->next)
		info->next = binfinal(info->next);
	return (info);
}

int	file_with_g_exit(char *order)
{
	int		i;
	char	*str;

	i = g_exit;
	str = ft_itoa(i);
	i = 0;
	while (str[i])
	{
		order[i] = str[i];
		i++;
	}
	return (strlen(str));
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

int	new_list(t_command *info, char text[1000], int *pos, char *order)
{
	if (info->pipe == 0)
		info->pipe = 1;
	info->next = mal_maillon();
	info = info->next;
	while (order[*pos] == '|')
		(*pos)++;
	(*pos)--;
	text[0] = '\0';
	return (-1);
}
