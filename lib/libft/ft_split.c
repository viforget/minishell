/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:32:32 by mberthet          #+#    #+#             */
/*   Updated: 2021/05/04 16:15:12 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countc(char const *s, int c)
{
	int				i;
	int				count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	ft_strlen_split(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_free(char **dest, int i)
{
	while (--i >= 0)
		free(dest[i]);
	free(dest);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		nb_c;
	int		i;

	i = 0;
	nb_c = ft_countc(s, c);
	dest = (char **)malloc(sizeof(char *) * (nb_c + 1));
	if (!dest)
		return (NULL);
	while (i < nb_c)
	{
		while (s && *s && *s == c)
			s++;
		dest[i] = ft_substr(s, 0, ft_strlen_split(s, c));
		if (!dest)
			return (ft_free(dest, i));
		s += ft_strlen_split(s, c);
		i++;
	}
	dest[i] = 0;
	return (dest);
}
