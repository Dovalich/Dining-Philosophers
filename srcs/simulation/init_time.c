/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:54:33 by nammari           #+#    #+#             */
/*   Updated: 2021/12/24 08:52:40 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_time(t_simulation_data *data)
{
	if (gettimeofday(&data->tv, NULL) == -1)
	{
		printf("There was an error with Gettimeofday\n");
		return (ERROR);
	}
	data->curr_time = 0;
	data->starting_time = (data->tv.tv_sec * 1000) + (data->tv.tv_usec / 1000);
	return (SUCCESS);
}

unsigned long	get_time(t_simulation_data *data)
{
	gettimeofday(&data->tv, NULL);
	return ((data->tv.tv_sec * 1000 + data->tv.tv_usec / 1000)
			- data->starting_time);
}

void	update_time(t_simulation_data *data)
{
	gettimeofday(&data->tv, NULL);
	data->curr_time = ((data->tv.tv_sec * 1000 + data->tv.tv_usec / 1000)
					- data->starting_time); 
}
