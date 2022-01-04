/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 01:00:36 by noufel            #+#    #+#             */
/*   Updated: 2022/01/04 06:26:31 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	all_philos_alive(t_philo *philo_lst, t_simulation_data *data)
{
	unsigned long	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (is_dead(philo_lst[i], data))
		{
			print_status(DIED, philo_lst);
			data->is_dead = true;
			return (false);
		}
		++i;
	}
	return (true);
}

void	*data_thread(void *data)
{
	t_simulation_data	*d;
	t_philo				*philo;

	d = data;
	philo = d->philo_lst;
	while (all_philos_alive(d->philo_lst, d))
	{
		usleep(1000);
		update_time(data);
	}
	return (NULL);
}
