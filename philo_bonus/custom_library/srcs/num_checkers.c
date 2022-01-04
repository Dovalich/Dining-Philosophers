/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 04:32:42 by nammari           #+#    #+#             */
/*   Updated: 2021/12/14 13:39:21 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_lib.h"

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
			&& ft_strcmp(str, u_long_max) > 0)
	{
		free(u_long_max);
		return (true);
	}
	free(u_long_max);
	return (false);
}
