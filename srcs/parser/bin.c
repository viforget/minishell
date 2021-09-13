/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 05:35:20 by lobertin          #+#    #+#             */
/*   Updated: 2021/09/13 15:00:52 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env(char **env, char *word)
{
	char	*line;
	int		x;
	int		y;

	x = 0;
	while (env[x])
	{
		y = 0;
		while (env[x][y] && (env[x][y] == word[y] || env[x][y] == 61))
		{
			if (env[x][y] == '=' && (word[y] == ' ' || !word[y]))
				return (x);
			y++;
		}
		x++;
	}
	return (-1);
}

int	set_index(char *order)
{
	if (ft_strcmp(order, "echo") == 0)
		return (1);
	if (ft_strcmp(order, "pwd") == 0)
		return (2);
	if (ft_strcmp(order, "env") == 0)
		return (3);
	if (ft_strcmp(order, "cd") == 0)
		return (4);
	if (ft_strcmp(order, "export") == 0)
		return (5);
	if (ft_strcmp(order, "unset") == 0)
		return (6);
	if (ft_strcmp(order, "exit") == 0)
		return (7);
	return (-1);
}

t_command	*set_bin(char *text, char **env, t_command *info)
{
	int			x;
	char		*path;
	char		**tab;
	struct stat	stt;

	path = NULL;
	info->index = set_index(text);
	if (info->index == -1 && text[0])
	{
		tab = ft_split(env[find_env(env, "PATH")] + 5, ':');
		x = 0;
		while (tab[x])
		{
			path = ft_strjoin2(tab[x], text);
			if (stat(path, &stt) == 0)
			{
				info->index = 0;
				info->bin = path;
				return (info);
			}
			free(path);
			x++;
		}
	}
	return (info);
}
