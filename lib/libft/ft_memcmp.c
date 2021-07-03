/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 14:18:45 by lobertin          #+#    #+#             */
/*   Updated: 2021/04/02 16:40:58 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	i = -1;
	ptr_s1 = (unsigned char *)s1;
	ptr_s2 = (unsigned char *)s2;
	while (++i < n)
		if (ptr_s1[i] != ptr_s2[i])
			return ((ptr_s1[i] - ptr_s2[i]));
	return (0);
}
