/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:13:19 by nammari           #+#    #+#             */
/*   Updated: 2021/12/24 10:46:17 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_dead(t_philo *philo, t_simulation_data *data)
{
	if (philo->is_alive == false)
		return (true);
	if (philo->last_ate_at)
	{
		if (get_time(philo->data) - philo->last_ate_at > data->time_to_die)
		{
			philo->is_alive = false;
			print_state(philo);
			return (true);
		}
	}
	return (false);
}

void	print_took_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->ts_print_mutex);
	printf("%03lu ms Philosopher [%lu] has taken left fork\n",
		philo->data->curr_time, philo->philo_nb);
	printf("%03lu ms Philosopher [%lu] has taken right fork\n",
		philo->data->curr_time, philo->philo_nb);
	pthread_mutex_unlock(&philo->ts_print_mutex);
}

void	print_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->ts_print_mutex);
	if (philo->is_alive == false)
	{
		printf("%03lu ms Philosopher [%lu] died\n",\
				philo->data->curr_time, philo->philo_nb);
	}
	else if (philo->is_eating)
	{
		printf("%03lu ms Philosopher [%lu] is eating\n",\
			philo->data->curr_time, philo->philo_nb);
	}
	else if (philo->is_sleeping)
	{
		printf("%03lu ms Philosopher [%lu] is sleeping\n",\
			philo->data->curr_time, philo->philo_nb);
	}
	else if (philo->is_thinking)
	{
		printf("%03lu ms Philosopher [%lu] is thinking\n",\
			philo->data->curr_time, philo->philo_nb);
	}
	pthread_mutex_unlock(&philo->ts_print_mutex);
}

void	start_eating(t_philo *philo, t_simulation_data *data)
{
	pthread_mutex_lock(&philo->mutex);
	pthread_mutex_lock(&philo->right_philo->mutex);
	if (is_dead(philo, data))
		return ;
	print_took_forks(philo);
	philo->is_eating = true;
	print_state(philo);
	while (get_time(philo->data) - data->curr_time < data->time_to_eat)
		usleep(10);
	update_time(philo->data);
	philo->last_ate_at = data->curr_time;
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->right_philo->mutex);
	pthread_mutex_unlock(&philo->mutex);
}

void	start_sleeping(t_philo *philo, t_simulation_data *data)
{
	philo->is_sleeping = true;
	print_state(philo);
	while (1)
	{
		if (is_dead(philo, data))
			return ;
		if (get_time(philo->data) - data->curr_time >= data->time_to_sleep)
			break ;
		usleep(10);
	}
	update_time(philo->data);
	philo->is_sleeping = false;
}

void	start_thinking(t_philo *philo, t_simulation_data *data)
{
	(void)data;
	philo->is_thinking = true;
	print_state(philo);
	philo->is_thinking = false;
	//sleep(100);
}
