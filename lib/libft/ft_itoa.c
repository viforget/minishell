/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 14:13:40 by lobertin          #+#    #+#             */
/*   Updated: 2021/04/02 16:45:17 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	int	get_length(int n)
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

char	*ft_itoa(int n)
{
	unsigned int	neg;
	char			*c_final;
	int				len;

	len = get_length(n);
	neg = n;
	c_final = malloc(sizeof(char) * (len + 1));
	if (!c_final)
		return (0);
	c_final[len] = '\0';
	(c_final[0] = '0');
	if (n == 0)
		return (c_final);
	if (n < 0)
	{
		c_final[0] = 45;
		neg *= -1;
	}
	while (neg != 0)
	{
		c_final[len - 1] = neg % 10 + '0';
		neg = neg / 10;
		len--;
	}
	return (c_final);
}
