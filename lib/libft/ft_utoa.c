/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 11:44:34 by lobertin          #+#    #+#             */
/*   Updated: 2021/05/16 22:16:09 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	int	get_length(unsigned int n)
{
	int				len;
	unsigned int	neg;

	len = 1;
	neg = n;
	if (n < 0)
	{
		len++;
		neg *= -1;
	}
	while (neg >= 10)
	{
		neg = neg / 10;
		len++;
	}
	return (len);
}

char	*itoa2(char *c_final, unsigned int neg, int len, unsigned int n)
{
	if (n < 0)
	{
		c_final[0] = 45;
		neg *= -1;
	}
	while (neg != 0)
	{
		c_final[len-- - 1] = neg % 10 + '0';
		neg = neg / 10;
	}
	return (c_final);
}

char	*ft_utoa(unsigned int n)
{
	unsigned int	neg;
	char			*c_final;
	int				len;

	len = get_length(n);
	neg = n;
	c_final = malloc(sizeof(char) * (len + 1));
	if (!(c_final))
		return (0);
	c_final[len] = '\0';
	if (n == 0)
	{
		c_final[0] = '0';
		return (c_final);
	}
	return (itoa2(c_final, neg, len, n));
}
