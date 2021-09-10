/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fornorm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 20:04:19 by viforget          #+#    #+#             */
/*   Updated: 2021/09/10 20:04:29 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	for_norm(t_command *info, char *order, int *pos, int *x)
{
	setg(info, order, *pos);
	(*pos)++;
	(*x)++;
}
