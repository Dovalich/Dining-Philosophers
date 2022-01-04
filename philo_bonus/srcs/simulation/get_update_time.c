/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_update_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:54:33 by nammari           #+#    #+#             */
/*   Updated: 2022/01/04 06:44:50 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

u_timestamp	get_time(void)
{
	struct timeval		tv;
	static u_timestamp	starting_time = 0;
	u_timestamp			time_since_epoch;
	u_timestamp			current_timestamp;

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

void	update_time(t_simulation_data *data)
{
	data->curr_time = get_time();
}
