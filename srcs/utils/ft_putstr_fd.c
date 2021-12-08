/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:28:43 by nammari           #+#    #+#             */
/*   Updated: 2021/12/08 14:30:31 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned	int ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		++i;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (str == NULL)
		return ;
	write(fd, str, ft_strlen(str));
}