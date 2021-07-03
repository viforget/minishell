/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 19:47:33 by lobertin          #+#    #+#             */
/*   Updated: 2021/04/02 16:17:59 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>
#include <unistd.h>
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

static size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;

	if (!dest || !src)
		return (ft_strlen(dest) + ft_strlen(src));
	dest_len = ft_strlen(dest);
	if (size == 0)
		return (ft_strlen(src));
	if ((int)size < 0)
		size = dest_len + ft_strlen(src) + 1;
	i = 0;
	while (dest_len + i < size - 1 && src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	if (size > dest_len)
		size = dest_len;
	return (size + ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*output;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	output = (char *)malloc(sizeof(char) * len + 1);
	if (!output)
		return (NULL);
	output[0] = '\0';
	ft_strlcat(output, s1, len + 1);
	ft_strlcat(output, s2, len + 1);
	return (output);
}
