/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_checkers_parsing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 04:32:42 by nammari           #+#    #+#             */
/*   Updated: 2021/12/12 16:04:55 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_num(char *str)
{
	if (str == NULL || *str == '\0')
		return (false);
	while (*str != '\0')
	{
		if (!(*str >= '0' && *str <= '9'))
			return (false);
		++str;
	}
	return (true);
}

bool	is_bigger_than_ulong_max(char *str)
{
	char	*u_long_max;

	if (str == NULL)
		return (false);
	while (*str == '0')
	{
		++str;	
	}
	u_long_max = ft_ultoa(ULONG_MAX);
	if (ft_strlen(str) > ft_strlen(u_long_max))
	{
		free(u_long_max);
		return (true);
	}
	else if (ft_strlen(str) == ft_strlen(u_long_max) 
			&& strcmp(str, u_long_max) > 0)
	{
		free(u_long_max);
		return (true);
	}
	free(u_long_max);
	return (false);
}

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

int	sizeof_ulong(unsigned long num)
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
