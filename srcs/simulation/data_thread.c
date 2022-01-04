/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 01:00:36 by noufel            #+#    #+#             */
/*   Updated: 2022/01/04 12:40:15 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	all_philos_ate(t_philo *head, unsigned long amount)
{
	t_philo	*head_ptr;

	head_ptr = head->right_philo;
	if (head->nb_time_ate < amount)
		return (false);
	while (head_ptr != head)
	{
		if (head_ptr->nb_time_ate < amount)
			return (false);
		head_ptr = head_ptr->right_philo;
	}
	return (true);
}

static bool	all_philos_alive(t_philo *head, t_simulation_data *data)
{
	t_philo	*head_ptr;
	unsigned long	nb_philos;

	head_ptr = head;
	nb_philos = data->nb_of_philo;
	while (nb_philos)
	{
		if (is_dead(head, data))
		{
			print_status(DIED, head);
			data->is_end = true;
			return (false);
		}
		--nb_philos;
		if (head->right_philo)
			head = head->right_philo;
	}
	return (true);
}

void	*data_thread(void *data)
{
	t_simulation_data	*d;
	t_philo				*philo;
	unsigned long		i;

	d = data;
	philo = d->philo_lst;
	i = 0;
	while (all_philos_alive(d->philo_lst, d))
	{
		if (all_philos_ate(philo, d->nb_time_to_eat))
		{
			pthread_mutex_lock(&d->ts_print);
			write(1, "Game Ended\n", 11);
			d->is_end = true;
			pthread_mutex_unlock(&d->ts_print);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
