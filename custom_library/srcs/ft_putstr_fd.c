/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:28:43 by nammari           #+#    #+#             */
/*   Updated: 2021/12/14 13:39:20 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_lib.h"

void	ft_putstr_fd(char *str, int fd)
{
	if (str == NULL)
		return ;
	write(fd, str, ft_strlen(str));
}