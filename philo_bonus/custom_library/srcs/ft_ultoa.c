/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:59:57 by nammari           #+#    #+#             */
/*   Updated: 2021/12/14 13:39:21 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_lib.h"

// Ft_ultoa takes an unsigned long and returns it in a malloc'd string format

static int	sizeof_ulong(unsigned long num)
{
	int				len;

	len = 0;
	while (num)
	{
		num /= 10;
		++len;
	}
	return (len);
}

char	*ft_ultoa(unsigned long num)
{
	int		len;
	char	*str;

	len = sizeof_ulong(ULONG_MAX);
	str = malloc(sizeof(*str) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	while (--len > -1)
	{
		str[len] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}
