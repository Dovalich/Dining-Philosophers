/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:39:58 by nammari           #+#    #+#             */
/*   Updated: 2022/01/04 06:44:50 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	start_odd_group(t_philo *head, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&head->thread, NULL, &philo_thread, (void *)head) != 0)
		{
			printf("Pthread_create faillure at Philosopher nb #%lu\n", head->id);
			return (error_message(THREAD_CREATION));
		}
		i += 2;
		if (head->right_philo != NULL && head->right_philo->right_philo)
			head = head->right_philo->right_philo;
		else
			return (0);
	}
	return (0);
}

static int start_even_group(t_philo *head, int nb_philo)
{
	int	i;

	i = 1;
	while (i < nb_philo)
	{
		if (pthread_create(&head->thread, NULL, &philo_thread, (void *)head) != 0)
		{
			printf("Pthread_create faillure at Philosopher nb #%lu\n", head->id);
			return (error_message(THREAD_CREATION));
		}
		i += 2;
		if (head->right_philo != NULL && head->right_philo->right_philo)
			head = head->right_philo->right_philo;
		else
			return (0);
	}
	return (0);
}

int	start_simulation(t_simulation_data *data, t_philo *head)
{
	t_philo *ptr;
	
	ptr = head->right_philo;
	if (start_even_group(ptr, data->nb_of_philo))
		return (ERROR);
	// usleep(1000);
	if (start_odd_group(head, data->nb_of_philo))
		return (ERROR);
	if (pthread_create(&data->thread, NULL, &data_thread, data) == -1)
		return (error_message(THREAD_CREATION));
	return (SUCCESS);
}

int	terminate_simulation(t_simulation_data *data, t_philo *philo)
{
	unsigned long	i;

	i = data->nb_of_philo;
	pthread_join(data->thread, NULL);
	pthread_mutex_destroy(&data->ts_print);
	while ((unsigned long)i > 0)
	{
		pthread_join(philo->thread, NULL);
		pthread_mutex_destroy(&philo->fork);
		if (philo->left_philo)
			philo = philo->left_philo;
		--i;
	}
	return (SUCCESS);
}
