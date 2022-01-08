/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:02:29 by nammari           #+#    #+#             */
/*   Updated: 2022/01/08 11:02:23 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_lib.h"

// Takes a string a converts it to Unsigned long

unsigned long	atoul(char *str)
{
	unsigned long	nb;

	if (str == NULL || *str == '\0')
		return (0);
	nb = 0;
	while (*str == ' ')
		++str;
	while (*str == '0')
		++str;
	while (*str)
	{
		nb = (nb * 10) + (*str - '0');
		++str;
	}
	return (nb);
}
