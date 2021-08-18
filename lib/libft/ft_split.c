/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 14:20:39 by lobertin          #+#    #+#             */
/*   Updated: 2021/07/07 12:30:04 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	word_c(const char *str, char c)
{
	int	i;
	int	nb_word;

	nb_word = 0;
	if (str[0] != c)
		nb_word++;
	i = 1;
	while (str[i])
	{
		if (str[i] != c && str[i - 1] == c)
			nb_word++;
		i++;
	}
	return (nb_word);
}

static char	*ft_strndup(char *src, int n)
{
	int		i;
	char	*copy;

	if (!src)
		return (NULL);
	i = 0;
	copy = NULL;
	if (!(copy = (char *)malloc((n + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < n)
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static char	**split_free(char **tab, int k)
{
	while (k)
	{
		free(tab[k]);
		k--;
	}
	free(tab);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	if (!s || !(tab = (char **)malloc((word_c(s, c) + 1) * sizeof(char *))))
		return (0);
	k = 0;
	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		if (j)
		{
			if (!(tab[k++] = ft_strndup((char *)&s[i], j)))
			{
				return (split_free(tab, k - 2));
			}
			i = i + j;
		}
		if (s[i])
			i++;
	}
	tab[k] = 0;
	return (tab);
}
