/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naddino <naddino@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:30:28 by naddino           #+#    #+#             */
/*   Updated: 2021/05/04 16:04:38 by naddino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	counter(char const *s1, char const *set)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (is_in_set(s1[i], set) && s1[i])
	{
		count++;
		i++;
	}
	if (s1[i])
	{
		i = ft_strlen(s1) - 1;
		while (is_in_set(s1[i], set))
		{
			count++;
			i--;
		}
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	count;
	size_t	len;
	size_t	i_s1;
	size_t	i_res;
	char	*res;

	if (!s1 || !set)
		return (0);
	count = counter(s1, set);
	len = ft_strlen(s1) - count;
	i_s1 = 0;
	i_res = 0;
	res = malloc(sizeof(*s1) * (len + 1));
	if (!res)
		return (0);
	res[len] = '\0';
	while (is_in_set(s1[i_s1], set) && s1[i_s1])
		i_s1++;
	while (i_res < len)
	{
		res[i_res] = s1[i_s1];
		i_s1++;
		i_res++;
	}
	return (res);
}
