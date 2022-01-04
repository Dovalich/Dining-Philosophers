/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:32:13 by nammari           #+#    #+#             */
/*   Updated: 2021/12/14 13:39:21 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_lib.h"

unsigned long ft_strlen(char *str)
{
	unsigned long	i;

	i = 0;
	if (str == NULL || *str == '\0')
		return (0);
	while (str[i])
		++i;
	return (i);
}
