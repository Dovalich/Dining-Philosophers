/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:54:33 by nammari           #+#    #+#             */
/*   Updated: 2022/01/03 15:06:01 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int	init_time()
// {
// 	if (gettimeofday(&data->tv, NULL) == -1)
// 	{

// 	data->curr_time = 0;
// 	data->starting_time = (data->tv.tv_sec * 1000) + (data->tv.tv_usec / 1000);
// 	return (SUCCESS);
// }

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
			printf("There was an error with Gettimeofday\n");
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
