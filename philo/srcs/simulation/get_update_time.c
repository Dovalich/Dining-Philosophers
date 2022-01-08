/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_update_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:54:33 by nammari           #+#    #+#             */
/*   Updated: 2022/01/08 11:36:38 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_u_timestamp	get_time(void)
{
	struct timeval			tv;
	static t_u_timestamp	starting_time = 0;
	t_u_timestamp			time_since_epoch;
	t_u_timestamp			current_timestamp;

	if (starting_time == 0)
	{
		if (gettimeofday(&tv, NULL) == -1)
		{
			ft_putstr_fd("There was an error with Gettimeofday\n", 2);
			return (ERROR);
		}
		starting_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
	gettimeofday(&tv, NULL);
	time_since_epoch = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	current_timestamp = time_since_epoch - starting_time;
	return (current_timestamp);
}

void	custom_usleep(t_u_timestamp sleep_for)
{
	t_u_timestamp	curr;
	t_u_timestamp	start;
	t_u_timestamp	end;

	start = get_time();
	end = start + sleep_for;
	while (1)
	{
		curr = get_time();
		if (curr >= end)
			break ;
		usleep(100);
	}
}
