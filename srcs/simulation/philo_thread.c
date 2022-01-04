/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:13:19 by nammari           #+#    #+#             */
/*   Updated: 2022/01/04 01:50:38 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_dead(t_philo *philo, t_simulation_data *data)
{
	if (data->is_dead == true)
		return (true);
	if (get_time() - philo->last_ate_at >= data->time_to_die)
		return (true);
	return (false);
}

void	start_eating(t_philo *philo, t_simulation_data *data)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->right_philo->fork);
	if (is_dead(philo, data))
		return ;
	print_status(TOOK_FORKS, philo);
	philo->last_ate_at = data->curr_time;
	print_status(EATING, philo);
	while (get_time() - philo->last_ate_at < data->time_to_eat)
	{
		usleep(50);
	}
	usleep(100);
	pthread_mutex_unlock(&philo->right_philo->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	start_sleeping(t_philo *philo, t_simulation_data *data)
{
	print_status(SLEEPING, philo);
	while (!data->is_dead)
	{
		if (get_time() - philo->last_ate_at + data->time_to_sleep >= data->time_to_sleep)
			break ;
		else if (data->curr_time - philo->last_ate_at >= data->time_to_die)
			break ;
		usleep(100);
	}
}

void	start_thinking(t_philo *philo)
{
	print_status(THINKING, philo);
	usleep(50);
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
	while (!philo->data->is_dead)
	{
		start_eating(philo, philo->data);
		if (is_dead(philo, philo->data))
			break ;
		start_sleeping(philo, philo->data);
		if (is_dead(philo, philo->data))
			break ;
		start_thinking(philo);
	}
	return (NULL);
}
