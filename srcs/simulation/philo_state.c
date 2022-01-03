/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:13:19 by nammari           #+#    #+#             */
/*   Updated: 2022/01/03 15:08:19 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_thread(void *philosopher)
{
	t_philo *philo;
	
	philo = (t_philo *)philosopher;
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
	print_status(TOOK_FORKS, philo);
	if (is_dead(philo, data))
		return ;
	philo->last_ate_at = data->curr_time;
	print_status(EATING, philo);
	while (get_time() - philo->last_ate_at < data->time_to_eat)
	{
		usleep(100);
	}
	pthread_mutex_unlock(&philo->right_philo->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	start_sleeping(t_philo *philo, t_simulation_data *data)
{
	print_status(SLEEPING, philo);
	while (!data->is_dead)
	{
		if (get_time() - data->curr_time >= data->time_to_sleep)
			break ;
		else if (data->curr_time - philo->last_ate_at >= data->time_to_die)
			break ;
		usleep(100);
	}
}

void	start_thinking(t_philo *philo)
{
	print_status(THINKING, philo);
	usleep(100);
}
