/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:36:14 by lobertin          #+#    #+#             */
/*   Updated: 2021/04/02 16:37:38 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(int nbr, char *base)
{
	int	diviseur;
	int	result;
	int	t_base;

	t_base = ft_strlen(base);
	if (nbr < 0)
	{
		ft_putchar_fd('-', 1);
		nbr = -(nbr);
	}
	diviseur = 1;
	while ((nbr / diviseur) >= t_base)
		diviseur = diviseur * t_base;
	while (diviseur > 0)
	{
		result = (nbr / diviseur) % t_base;
		ft_putchar_fd(base[result], 1);
		diviseur = diviseur / t_base;
	}
}
