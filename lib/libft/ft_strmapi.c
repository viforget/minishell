/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 14:21:22 by lobertin          #+#    #+#             */
/*   Updated: 2021/04/02 13:28:39 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_strlen(const char *s)
{
	size_t	x;

	x = 0;
	while (s[x])
		x++;
	return (x);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	x;

	str = malloc(sizeof(char) * ft_strlen(s) + 1);
	if ((!s) || (!str))
		return (NULL);
	x = 0;
	while (s[x])
	{
		str[x] = (f)(x, s[x]);
		x++;
	}
	str[x] = '\0';
	return (str);
}
