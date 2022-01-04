/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:13:19 by nammari           #+#    #+#             */
/*   Updated: 2022/01/04 17:52:17 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock_fork(t_philo *philo, t_simulation_data *data)
{
	(void)data;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[philo->id % data->nb_of_philo]);
		pthread_mutex_lock(&philo->forks[philo->id - 1]);	
	}
	else
	{
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
		pthread_mutex_lock(&philo->forks[philo->id % data->nb_of_philo]);
	}
}

void	unlock_fork(t_philo *philo, t_simulation_data *data)
{
	(void)data;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->forks[philo->id % data->nb_of_philo]);
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);

	}
	else
	{
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->forks[philo->id % data->nb_of_philo]);
	}	
}

void	start_eating(t_philo *philo, t_simulation_data *data)
{
	lock_fork(philo, data);
	philo->last_ate_at = get_time();
	if (philo->data->is_end)
	{
		unlock_fork(philo, data);
		return ;
	}
	print_status(TOOK_FORKS, philo);
	print_status(EATING, philo);
	philo->nb_time_ate += 1;
	custom_usleep(data->time_to_eat);
	unlock_fork(philo, data);
}

void	start_sleeping(t_philo *philo, t_simulation_data *data)
{
	u_timestamp	curr;
	print_status(SLEEPING, philo);
	curr = get_time();
	custom_usleep(data->time_to_sleep);
}

void	*philo_thread(t_philo *philo)
{
	if (philo->data->nb_of_philo == 1)
	{
		print_status(TOOK_LEFT_FORK, philo);
		usleep(philo->data->time_to_die * 1000);
	}
	while (!philo->data->is_end)
	{
		start_eating(philo, philo->data);
		if (philo->data->is_end)
			break ;
		start_sleeping(philo, philo->data);
		if (philo->data->is_end)
			break ;
		print_status(THINKING, philo);
		usleep(100);
	}
	return (NULL);
}
