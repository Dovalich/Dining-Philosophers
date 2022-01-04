/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:39:58 by nammari           #+#    #+#             */
/*   Updated: 2022/01/04 17:48:05 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int start_odd_group(t_philo *philo_lst, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&philo_lst[i].thread, NULL, (void *)&philo_thread, &philo_lst[i]) != 0)
		{
			printf("Pthread_create faillure at Philosopher nb #%lu\n", philo_lst[i].id);
			return (error_message(THREAD_CREATION));
		}
		i += 2;
	}
	return (0);
}

static int start_even_group(t_philo *philo_lst, int nb_philo)
{
	int	i;

	i = 1;
	while (i < nb_philo)
	{
		if (pthread_create(&philo_lst[i].thread, NULL, (void *)&philo_thread, &philo_lst[i]) != 0)
		{
			printf("Pthread_create faillure at Philosopher nb #%lu\n", philo_lst[i].id);
			return (error_message(THREAD_CREATION));
		}
		i += 2;
	}
	return (0);
}

int	start_simulation(t_simulation_data *data, t_philo *philo_lst)
{
	if (start_even_group(philo_lst, data->nb_of_philo))
		return (ERROR);
	usleep(1000);
	if (start_odd_group(philo_lst, data->nb_of_philo))
		return (ERROR);
	if (pthread_create(&data->thread, NULL, &data_thread, data) == -1)
		return (error_message(THREAD_CREATION));
	return (SUCCESS);
}

int	terminate_simulation(t_simulation_data *data, t_philo *philo_lst)
{
	unsigned long	i;

	pthread_join(data->thread, NULL);
	pthread_mutex_destroy(&data->ts_print);
	i = 0;
	while ((unsigned long)i < data->nb_of_philo)
	{
		pthread_join(philo_lst[i].thread, NULL);
		pthread_mutex_destroy(&philo_lst[i].forks[i]);
		++i;
	}
	free(philo_lst->forks);
	free(philo_lst);
	return (SUCCESS);
}
