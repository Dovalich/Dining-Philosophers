/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 01:00:36 by noufel            #+#    #+#             */
/*   Updated: 2022/01/04 01:51:42 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
			data->is_dead = true;
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
		usleep(100);
		update_time(data);
	}
	return (NULL);
}
