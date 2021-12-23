/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:13:19 by nammari           #+#    #+#             */
/*   Updated: 2021/12/23 15:14:58 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_philo *philo)
{
	if (philo->is_eating)
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
}

void	start_eating(t_philo *philo, t_simulation_data *data)
{
	pthread_mutex_lock(&data->mutex);
	philo->is_eating = true;
	print_state(philo);
	pthread_mutex_unlock(&data->mutex);
	if (philo->time_to_die < philo->time_to_eat)
	{
		philo->is_alive = false;
		return ;
	}
	while (get_time(philo->data) - philo->data->curr_time < philo->data->time_to_eat)
	{
		usleep(10);
	}
	update_time(philo->data);
	philo->time_to_die = data->time_to_die;
	return ;
}

void	drop_forks(t_philo *philo)
{
	philo->right_philo->fork_on_table = true;
	philo->fork_on_table = true;
	printf("%03lu ms Philosopher [%lu] has put right fork down\n",
		philo->data->curr_time, philo->philo_nb);
	printf("%03lu ms Philosopher [%lu] has put left fork down \n",
		philo->data->curr_time, philo->philo_nb);
	pthread_mutex_unlock(&philo->right_philo->mutex);
	pthread_mutex_unlock(&philo->mutex);
}

void	get_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	pthread_mutex_lock(&philo->right_philo->mutex);
	philo->fork_on_table = false;
	philo->right_philo->fork_on_table = false;
	printf("%03lu ms Philosopher [%lu] has taken left fork\n",
		philo->data->curr_time, philo->philo_nb);
	printf("%03lu ms Philosopher [%lu] has taken right fork\n",
		philo->data->curr_time, philo->philo_nb);	
}

void	start_sleeping(t_philo *philo)
{
	if (philo->time_to_die < philo->time_to_sleep)
	{
		philo->is_alive = false;
		return ;
	}
	print_state(philo);
	ft_usleep(philo->time_to_sleep);
	update_time(philo->data);
}
