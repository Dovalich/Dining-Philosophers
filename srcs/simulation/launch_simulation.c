/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:39:58 by nammari           #+#    #+#             */
/*   Updated: 2021/12/24 10:40:50 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_thread(void *philosopher)
{
	t_philo *philo;
	
	philo = (t_philo *)philosopher;
	if (philo->philo_nb % 2 != 0)
		usleep(100);
	while (true)
	{
	// Start of the critical section
		start_eating(philo, philo->data);
		start_sleeping(philo, philo->data);
		start_thinking(philo, philo->data);
	// end of the critical section
	}
	return (NULL);
}

bool	all_philos_alive(t_philo *head)
{
	t_philo	*head_ptr;

	head_ptr = head;
	while (head->right_philo != head_ptr)
	{
		if (head->is_alive == false)
			return (false);
		head = head->right_philo;
	}
	return (true);
}

void	*data_thread(void *data)
{
	t_simulation_data	*d;
	t_philo				*philo;
	unsigned long		i;

	d = data;
	philo = d->philo_lst;
	i = 0;
	while (all_philos_alive(d->philo_lst))
	{
		usleep(5);
		continue;
	}
	while (i < d->nb_of_philo)
	{
		pthread_detach(philo->thread);
		philo = philo->right_philo;
		++i;
	}
	return (NULL);
}


int	start_simulation(t_simulation_data *data, t_philo *head)
{
	int			i;

	i = 0;
	pthread_create(&data->thread, NULL, &data_thread, data);
	while ((unsigned long)i < data->nb_of_philo)
	{
		if (pthread_create(&head->thread, NULL, &philo_thread, (void *)head) != 0)
		{
			if (head == NULL)
				printf("Pthread_create faillure at Philosopher #%p\n", head);
			else
				printf("Pthread_create faillure at Philosopher nb #%lu\n", head->philo_nb);
		}
		++i;
		if (head->right_philo != NULL)
			head = head->right_philo;
	}
	pthread_join(data->thread, NULL);
	// while ((unsigned long)i > 0)
	// {
	// 	pthread_join(head->thread, NULL);
	// 	head = head->left_philo;
	// 	--i;
	// 	printf("joinin\n");
	// }
	return (SUCCESS);
}
