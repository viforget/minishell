/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 05:35:20 by lobertin          #+#    #+#             */
/*   Updated: 2021/09/15 13:56:10 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	use_find(char **env, char *word)
{
	int	nb;

	nb = find_env(env, word + 1);
	free(word);
	return (nb);
}

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

t_command	*ft_info(t_command *info, char *path, char **tab, char *text)
{
	info->index = 0;
	info->bin = path;
	free_env(tab);
	free(text);
	return (info);
}

t_command	*set_bin(char *text, char **env, t_command *info)
{
	int			x;
	char		*path;
	char		**tab;
	struct stat	stt;

	path = NULL;
	info->index = set_index(text);
	if (info->index == -1 && text[0] && find_env(env, "PATH") != -1)
	{
		tab = ft_split(env[find_env(env, "PATH")] + 5, ':');
		x = 0;
		while (tab[x])
		{
			path = ft_strjoin2(tab[x], text);
			if (stat(path, &stt) == 0)
				return (ft_info(info, path, tab, text));
			free(path);
			x++;
		}
		free_env(tab);
	}
	free(text);
	return (info);
}
