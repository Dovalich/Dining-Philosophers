/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:04:34 by nammari           #+#    #+#             */
/*   Updated: 2022/01/03 13:21:18 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(u_timestamp sleep_time)
{
	u_timestamp	i;

	i = 0;
	while (i < sleep_time)
	{
		usleep(10);
		++i;
	}
}

// while current_time != the time I want -> ft_usleep (~ 1 micro);