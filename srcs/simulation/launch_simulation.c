/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:39:58 by nammari           #+#    #+#             */
/*   Updated: 2021/12/17 12:41:21 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*print_hi(void *philo)
{
	t_philo *ptr;
	
	ptr = (t_philo *)philo;
	ptr->fork_on_table = true;
	if (ptr->data->nb_of_philo % 2 == 0 && ptr->philo_nb % 2 != 0)
		usleep(5);
	if (ptr->left_philo->fork_on_table)
		printf("Philosopher nb %lu has taken left fork\n", ptr->philo_nb);
	if (ptr->right_philo->fork_on_table)
		printf("Philosopher nb %lu has taken right fork\n", ptr->philo_nb);
	return (NULL);
}

// int	launch_philo_even(t_simulation_data *data, t_philo *head)
// {
// 	int	i;

// 	i = 0;
	
// }

int	launch_simulation(t_simulation_data *data, t_philo *head)
{
	int	i;
	// pthread_t	main_thread;

	i = 0;
	// if (data-> nb_of_philo % 2 == 0)
	// 	//launch_philosopher_even(head, data);
	// else
	// 	//launch_philosopher_odd(head, data);
	// launch_data_thread(head, data);
	while ((unsigned long)i < data->nb_of_philo)
	{
		head->fork_on_table = true;
		if (pthread_create(&head->thread, NULL, &print_hi, (void *)head) != 0)
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
	i = 0;
	while ((unsigned long)i < data->nb_of_philo)
	{
		pthread_join(head->thread, NULL);
		head = head->left_philo;
		++i;
	}
	return (SUCCESS);
}
