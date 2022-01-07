/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 01:00:36 by noufel            #+#    #+#             */
/*   Updated: 2022/01/07 17:02:25 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_dead(t_philo philo, t_buttler *data)
{
	if (data->is_end == true)
		return (true);
	if (get_time() - philo.last_ate_at >= data->time_to_die)
		return (true);
	return (false);
}

bool	all_philos_ate(t_philo *philo_lst, t_buttler *data)
{
	unsigned long	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (philo_lst[i].nb_time_ate < data->nb_time_to_eat)
			return (false);
		++i;
	}
	return (true);
}

static bool	all_philos_alive(t_philo *philo_lst, t_buttler *data)
{
	unsigned long	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (is_dead(philo_lst[i], data))
		{
			print_status(DIED, philo_lst);
			data->is_end = true;
			return (false);
		}
		++i;
	}
	return (true);
}

void	*data_thread(void *data)
{
	t_buttler	*d;
	t_philo				*philo;
	unsigned long		i;

	d = data;
	philo = d->philo_lst;
	i = 0;
	while (all_philos_alive(d->philo_lst, d))
	{
		if (all_philos_ate(philo, d))
		{
			pthread_mutex_lock(&d->ts_print);
			write(1, "Game Ended\n", 11);
			d->is_end = true;
			pthread_mutex_unlock(&d->ts_print);
			return (NULL);
		}
		usleep(200);
	}
	return (NULL);
}
