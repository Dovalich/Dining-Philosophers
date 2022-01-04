/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:13:19 by nammari           #+#    #+#             */
/*   Updated: 2022/01/04 15:20:38 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_dead(t_philo *philo, t_simulation_data *data)
{
	if (data->is_end == true)
		return (true);
	if (get_time() - philo->last_ate_at >= data->time_to_die)
		return (true);
	return (false);
}

unsigned int	get_hungriest_philo(t_philo *philo)
{
	u_timestamp		farthest_last_ate;
	unsigned long	philo_nb;
	t_philo			*ptr;

	ptr = philo;
	farthest_last_ate = philo->last_ate_at;
	philo_nb = philo->id;
	while (1)
	{
		ptr = ptr->right_philo;
		if (ptr == philo)
			break ;
		if (farthest_last_ate > ptr->last_ate_at)
		{
			farthest_last_ate = ptr->last_ate_at;
			philo_nb = ptr->id;
		}
	}
	// printf("the hungriest philo is %lu\n", philo_nb);
	return (philo_nb);
}

void	lock_fork(t_philo *philo, t_simulation_data *data)
{
	(void)data;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_philo->fork);
		pthread_mutex_lock(&philo->fork);		
	}
	else
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->right_philo->fork);	
	}
}

void	unlock_fork(t_philo *philo, t_simulation_data *data)
{
	(void)data;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->right_philo->fork);
		pthread_mutex_unlock(&philo->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->right_philo->fork);
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
	custom_usleep(data->time_to_eat);
	philo->nb_time_ate += 1;
	unlock_fork(philo, data);
}

void	start_sleeping(t_philo *philo, t_simulation_data *data)
{
	u_timestamp	curr;

	print_status(SLEEPING, philo);
	curr = get_time();
	custom_usleep(data->time_to_sleep);
}

void	*philo_thread(void *philosopher)
{
	t_philo *philo;
	
	philo = (t_philo *)philosopher;
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
