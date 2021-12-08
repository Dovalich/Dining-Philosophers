/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:14:58 by nammari           #+#    #+#             */
/*   Updated: 2021/12/08 16:08:41 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	global = 0;

void	*routine(void *mutex)
{
	int	i;

	i = 0;
	while (i < 1000000)
	{
		++i;
		pthread_mutex_lock(mutex);
		global++;
		pthread_mutex_unlock(mutex);
	}
	return (NULL);
}

void	print_list(t_philo *head, t_simulation_data *data)
{
	unsigned long		i;
	
	i = 0;
	if (head == NULL)
		printf("List is Empty.\n");
	else
	{
		while (i < data->nb_of_philo) 
		{
			++i;
			printf("This is Philo nb #%0lu. To my Left Philo_nb #%0lu and to My Right Philo_nb #%0lu\n", head->philo_nb, head->left_philo->philo_nb, head->right_philo->philo_nb);
			head = head->right_philo;
		}
	}
}

int	main(int argc, char **argv)
{
	t_simulation_data	data;
	t_philo				*head;
	(void)argv;
	
	if (argc > 5)
		return (ERROR);
	//if (parse_input(&data) != SUCCESS)
	//	return (ERROR);
	data.has_nb_time_to_eat = true;
	data.nb_of_philo = 5;
	data.nb_time_to_eat = 1;
	data.starting_time = 10;
	data.time_to_die = 20;
	data.time_to_eat = 30;
	data.time_to_sleep = 40;
	head = create_philosopher_linked_list(&data);
	if (head == NULL)
		return (ERROR);
	print_list(head, &data);
	if (init_time(&data))
		return (ERROR);
	// if (launch_simulation(&data))
	// 	return (ERROR);
	return (SUCCESS);
}