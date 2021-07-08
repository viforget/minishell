/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 19:12:45 by lobertin          #+#    #+#             */
/*   Updated: 2021/07/08 09:09:48 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_env(char **env, char *word)
{
	char	*line;
	int		x;
	int		y;
	while(env[x])
	{
		y = 0;
		while(env[x][y] && word[y] && (env[x][y] == word[y] || env[x][y]== '='))
		{
			y++;
			if(env[x][y]== '=')
				return (x);
		}
		x++;
	}
	return (0);
}

int set_index(char *order)
{
	printf("");
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

t_command	*fonction(char *text, int pos, char **env, t_command *info)
{
	char		*path[2];
	int 		size;
	char		**tab;
	int			x;
	struct stat	stt;
	
	info->index = set_index(text);
	tab = ft_split(env[find_env(env, "PATH")], '=');
	
	if(info->index == -1)
	{
		tab = ft_split(tab[1], ':');
		x = 0;
		while(tab[x])
		{
			path[0] = ft_strjoin("/",text);
			path[1] = ft_strjoin(tab[x],path[0]);
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

char	*find_next_word(char *order)
{
	int		pos;
	char	*word;
	int		size;
	int		x;

	pos = 0;
	size = 0;
	x = 0;
	while (order[pos] == '=')
		pos++;
	if (order[pos] == 34)
		while (order[pos + size] != 34)
			size++;
	else if (order[pos] == 39)
		while (order[pos + size] != 39)
			size++;
	else
		while (order[pos + size] != ' ')
			size++;
	word = malloc(sizeof(char) * size);
	while (size--)
		word[x++] = order[pos++];
	return (word);
}

char	*executable(char *order)
{
	int		size;
	int		pos;
	char	*path;

	size = 0;
	while (!(ft_strchr(" ", order[size - 1])))
		size++;
	path = malloc(sizeof(char)* size);
	pos = 0;
	while (pos <= size)
	{
		path[pos] = order[pos];
		pos++;
	}
	return (path);
}

char *cut(char *order)
{
	char *re;
	int x;
	int y;

	x = 0;
	re = malloc(sizeof(char));
	if (order[x] == ' ')
		x++;
	y = 0;
	while(order[x] != ' ')
	{
		re[y] = order[x];
		x++;
		y++;
	}
	return(re);
}

t_command	*parser(char *order, char **env)
{
	int			pos;
	char		text[20];
	t_command	*info;
	t_command	*save;
	int t;
	int try = 0;

	t = 0;
	info = malloc(sizeof(t_command));
	save = info;
	pos = 0;
	while (order[pos])
	{
		if (ft_strchr(" =.|;<>", order[pos]))
		{
			try = 0;
			t = 1;
			/*if (order[pos] == '=' && pos > 0)
				variable(order, pos, text, env);
			else*/ if (order[pos] == '.')
				info->bin = executable(order + pos);
			else if (order[pos] == ' ' && (info->index <= 7 || info->index >= -1))
				{
					info = fonction(cut(text), pos, env, info);
				}
			else if (order[pos] == '|')
			{
				t = 0;
				text[0] = '\0';
				info->pipe = 1;
				info->next = malloc(sizeof(t_command));
				info = info->next;
			}
			else if (order[pos] == ';')
			{
				t = 0;
				info->pipe = 0;
				info->next = malloc(sizeof(t_command));
				info = info->next;
			}
			else if (order[pos] == '>' && order[pos + 1] != '>')
			{
				info->pipe = 2;
				info->file = find_next_word(order + pos);
			}
			else if (order[pos] == '>' && order[pos + 1] == '>')
			{
				info->pipe = 3;
				info->file = find_next_word(order + pos);
			}
			else if (order[pos] == '<')
			{
				info->pipe = 4;
				info->file = find_next_word(order + pos);
			}
			else
			{
			//	pos++;
				t = 0;
			}
		}
		text[try] = order[pos];
		text[try + 1] = 0;
		pos++;
		try++;
	}
	if (t == 0 || info -> index == -1)
	{
		info = fonction(cut(text), pos, env, info);
	}
	info->next = NULL;
	return (save);
}