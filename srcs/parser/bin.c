/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 05:35:20 by lobertin          #+#    #+#             */
/*   Updated: 2021/09/01 16:56:19 by lobertin         ###   ########.fr       */
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
	if (strcmp(order, "echo") == 0)
		return (1);
	if (strcmp(order, "pwd") == 0)
		return (2);
	if (strcmp(order, "env") == 0)
		return (3);
	if (strcmp(order, "cd") == 0)
		return (4);
	if (strcmp(order, "export") == 0)
		return (5);
	if (strcmp(order, "unset") == 0)
		return (6);
	if (strcmp(order, "exit") == 0)
		return (7);
	return (-1);
}

t_command	*set_bin(char *text, char **env, t_command *info)
{
	int			x;
	char		*path[2];
	char		**tab;
	struct stat	stt;

	path[0] = NULL;
	path[1] = NULL;
	info->index = set_index(text);
	if (info->index == -1 && text[0])
	{
		tab = ft_split(env[find_env(env, "PATH")], '=');
		tab = ft_split(tab[1], ':');
		x = 0;
		while (tab[x])
		{
			path[0] = ft_strjoin("/", text);
			path[1] = ft_strjoin(tab[x], path[0]);
			free(path[0]);
			if (stat(path[1], &stt) == 0)
			{
				info->index = 0;
				info->bin = path[1];
				return (info);
			}
			free(path[1]);
			x++;
		}
	}
	return (info);
}
