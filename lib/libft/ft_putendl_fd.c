/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobertin <lobertin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 14:19:42 by lobertin          #+#    #+#             */
/*   Updated: 2021/04/02 16:36:56 by lobertin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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

void	ft_putendl_fd(char const *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
