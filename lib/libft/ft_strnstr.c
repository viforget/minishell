/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 14:22:29 by lobertin          #+#    #+#             */
/*   Updated: 2021/04/02 13:27:17 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>

static size_t	ft_strlen(const char *s)
{
	size_t	x;

	x = 0;
	while (s[x])
	{
		x++;
	}
	return (x);
}

char	*ft_strnstr(const char *haystack,
				const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!ft_strlen(needle))
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] && haystack[i + j] && needle[j] == haystack[i + j]
			&& (i + j) < len)
			j++;
		if (!needle[j])
			return ((char *)&haystack[i]);
		i++;
	}
	return (0);
}
