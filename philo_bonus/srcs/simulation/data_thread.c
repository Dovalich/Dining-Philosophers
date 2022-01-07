/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 01:00:36 by noufel            #+#    #+#             */
/*   Updated: 2022/01/07 22:03:21 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*buttler_thread(void *dat)
{
	t_buttler	*data;

	data = (t_buttler *)dat;
	data->end_simulation = sem_open(SEM_NAME_END, 0);
	if (data->end_simulation == SEM_FAILED)
		return (NULL);
	while (!data->is_end)
	{
		if (sem_wait(data->end_simulation) == -1)
		{
			data->is_end = true;
			return (NULL);
		}
		else
			sem_post(data->end_simulation);
		if (data->philo->nb_time_ate == data->nb_time_to_eat)
		{
			sem_wait(data->print_ts);
			write(1, "Game Ended\n", 11);
			data->is_end = true;
			sem_post(data->print_ts);
			return (NULL);
		}
		else if (get_time() - data->philo->last_ate_at >= 0)
		{
			print_status(DIED, data->philo);
			data->is_end = true;
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
