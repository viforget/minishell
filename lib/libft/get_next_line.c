/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:14:10 by viforget          #+#    #+#             */
/*   Updated: 2021/06/14 16:12:03 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_n(char str[])
{
	size_t	n;

	n = 0;
	while (str && str[n] && str[n] != SEP)
		n++;
	return (n);
}

static char	*ft_strjoind(char *s1, char const *s2)
{
	int		i;
	int		i2;
	char	*str;
	int		len;

	i = 0;
	i2 = 0;
	if (!s2)
		return (NULL);
	len = ft_strlen(s1) + find_n((char *)s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s1 && s1[i] != '\0')
		str[i2++] = s1[i++];
	i = 0;
	while (s2[i] != '\0' && s2[i] != SEP)
		str[i2++] = s2[i++];
	str[i2] = '\0';
	free(s1);
	return (str);
}

static int	fill_zero(char str[], ssize_t nb)
{
	if (nb >= 0)
		while (nb <= BUFFER_SIZE)
			str[nb++] = 0;
	return (0);
}

static	int	cut_str(char str[], size_t n)
{
	size_t	i;

	i = 0;
	while (n < BUFFER_SIZE)
		str[i++] = str[n++];
	while (i < BUFFER_SIZE)
		str[i++] = 0;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	buf[BUFFER_SIZE + 1];
	ssize_t		rd;

	if (fd < 0 || fd > OPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (-1);
	*line = ft_strjoind(NULL, buf);
	rd = BUFFER_SIZE;
	if (find_n(buf) != ft_strlen(buf))
		return (cut_str(buf, find_n(buf) + 1));
	while (rd == BUFFER_SIZE)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd < 0)
			return (-1);
		fill_zero(buf, rd);
		*line = ft_strjoind(*line, buf);
		if (rd == BUFFER_SIZE)
			rd = find_n(buf);
	}
	if (find_n(buf) == ft_strlen(buf))
		return (fill_zero(buf, 0));
	cut_str(buf, find_n(buf) + 1);
	return (1);
}
