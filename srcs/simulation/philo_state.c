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
	print_took_forks(philo);
	if (is_dead(philo, data))
		return ;
	if (philo->last_ate_at)
		philo->last_ate_at = data->curr_time;
	philo->is_eating = true;
	print_state(philo);
	printf("this is philo's %lu last ate at %llu\n",philo->philo_nb, philo->last_ate_at);
	while (get_time() - philo->last_ate_at < data->time_to_eat)
	{
		usleep(100);
	}
	printf("philo nb %lu's current time is %llu\n", philo->philo_nb, data->curr_time);
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->right_philo->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	start_sleeping(t_philo *philo, t_simulation_data *data)
{
	philo->is_sleeping = true;
	print_state(philo);
	while (!data->is_dead)
	{
		if (get_time() - data->curr_time >= data->time_to_sleep)
			break ;
		else if (data->curr_time - philo->last_ate_at >= data->time_to_die)
			break ;
		usleep(100);
	}
	// update_time(data);
	philo->is_sleeping = false;
}

void	start_thinking(t_philo *philo, t_simulation_data *data)
{
	(void)data;
	philo->is_thinking = true;
	print_state(philo);
	philo->is_thinking = false;
	usleep(100);
}

void	print_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->ts_print);
	if (philo->is_alive == false || philo->data->is_dead == true)
	{
		printf("inside print state is alive == false\n");
		pthread_mutex_unlock(&philo->data->ts_print);
		return ;
	}
	else if (philo->is_eating)
	{
		printf("%03llu ms Philosopher [%lu] is eating\n",\
			philo->data->curr_time, philo->philo_nb);
	}
	else if (philo->is_sleeping)
	{
		printf("%03llu ms Philosopher [%lu] is sleeping\n",\
			philo->data->curr_time, philo->philo_nb);
	}
	else if (philo->is_thinking)
	{
		printf("%03llu ms Philosopher [%lu] is thinking\n",\
			philo->data->curr_time, philo->philo_nb);
	}
	pthread_mutex_unlock(&philo->data->ts_print);
}

void	print_took_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->ts_print);
	if (philo->is_alive == false || philo->data->is_dead == true)
	{
		printf("inside print forks == false\n");
		pthread_mutex_unlock(&philo->data->ts_print);
		return ;
	}
	printf("%03llu ms Philosopher [%lu] has taken left fork\n",
		philo->data->curr_time, philo->philo_nb);
	printf("%03llu ms Philosopher [%lu] has taken right fork\n",
		philo->data->curr_time, philo->philo_nb);
	pthread_mutex_unlock(&philo->data->ts_print);
}