/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:13:19 by nammari           #+#    #+#             */
/*   Updated: 2022/01/04 06:29:32 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_dead(t_philo philo, t_simulation_data *data)
{
	if (data->is_dead == true)
		return (true);
    // printf("This is is alive %d and time to die %lu\n", philo->is_alive, philo->id);
	if (get_time() - philo.last_ate_at >= data->time_to_die)
		return (true);
	return (false);
}

// unsigned int	get_hungriest_philo(t_philo *philo)
// {
// 	u_timestamp		farthest_last_ate;
// 	unsigned int	philo_nb;
// 	t_philo			*ptr;

// 	ptr = philo;
// 	farthest_last_ate = philo->last_ate_at;
// 	philo_nb = philo->id;
// 	while (1)
// 	{
// 		ptr = ptr->right_philo->right_philo;
// 		if (ptr == philo)
// 			break ;
// 		if (farthest_last_ate > ptr->last_ate_at)
// 		{
// 			farthest_last_ate = ptr->last_ate_at;
// 			philo_nb = ptr->id;
// 		}
// 	}
// 	return (philo_nb);
// }

void	start_eating(t_philo *philo, t_simulation_data *data)
{
	// if (philo->last_ate_at && philo->id != get_hungriest_philo(philo))
	// 	usleep(400);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[philo->id + 1]);
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[philo->id - 1]);	
		pthread_mutex_lock(&philo->forks[philo->id + 1]);
	}
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->forks[philo->id + 1]);
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);
		return ;
	}
	print_status(TOOK_FORKS, philo);
	philo->last_ate_at = data->curr_time;
	print_status(EATING, philo);
	while (1)
	{
		if (get_time() - philo->last_ate_at >= data->time_to_eat)
			break ;
		usleep(100);
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->forks[philo->id + 1]);
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->forks[philo->id + 1]);
	}
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
	usleep(100);
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
		if (philo->data->is_dead)
			break ;
		start_sleeping(philo, philo->data);
		if (philo->data->is_dead)
			break ;
		start_thinking(philo);
	}
	return (NULL);
}
