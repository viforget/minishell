/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 19:42:50 by lobertin          #+#    #+#             */
/*   Updated: 2021/04/02 13:22:04 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>
#include <stdlib.h>

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*output;
	size_t	i;
	size_t	size;
	char	*vide;

	vide = (char *)malloc(0);
	if (s)
		size = ft_strlen(s);
	if (!s || size < start)
		return (vide);
	if (!(start + len < size))
		len = size - start;
	output = (char *)malloc((len + 1) * sizeof(char));
	if (!(output))
		return (0);
	i = 0;
	while (s[start + i] && i < len)
	{
		output[i] = s[start + i];
		i++;
	}
	output[i] = '\0';
	return (output);
}
