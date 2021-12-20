/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:39:58 by nammari           #+#    #+#             */
/*   Updated: 2021/12/20 13:28:27 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
void	philo_eat(t_philo *philo, t_simulation_data *data)
{
	unsigned long	time_to_eat;

	(void)philo;
	time_to_eat = data->curr_time;
	usleep(10000);
	return ;
	// while (data->curr_time < time_to_eat + data->time_to_eat)
	// {
	// 	usleep(100);
	// }
}

void	get_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_philo->mutex);
	printf("%03lu ms Philosopher [%lu] has taken left fork\n",philo->data->curr_time, philo->philo_nb);
	philo->left_philo->fork_on_table = false;

	pthread_mutex_lock(&philo->right_philo->mutex);
	printf("%03lu ms Philosopher [%lu] has taken right fork\n",philo->data->curr_time, philo->philo_nb);
	philo->right_philo->fork_on_table = false;

	philo_eat(philo, philo->data);
	philo->right_philo->fork_on_table = true;
	printf("%03lu ms Philosopher [%lu] has put right fork down\n",philo->data->curr_time, philo->philo_nb);
	pthread_mutex_unlock(&philo->right_philo->mutex);
	philo->left_philo->fork_on_table = true;
	printf("%03lu ms Philosopher [%lu] has put left fork down \n",philo->data->curr_time, philo->philo_nb);
	pthread_mutex_unlock(&philo->left_philo->mutex);
}


void	*philo_thread(void *philo)
{
	t_philo *ptr;
	
	ptr = (t_philo *)philo;
	if (ptr->philo_nb % 2 != 0 && ptr->data->nb_of_philo % 2 == 0)
		usleep(5000);
	get_forks(ptr);
	return (NULL);
}

bool	all_philos_alive(t_philo *head)
{
	t_philo	*head_ptr;

	head_ptr = head;
	while (head->right_philo != head_ptr)
	{
		if (head->time_to_die == 0)
			return (false);
		head = head->right_philo;
	}
	return (true);
}

void	*data_thread(void *data)
{
	t_simulation_data	*d;

	d = data;
	while (all_philos_alive(d->philo_lst))
	{
		continue;
	}
	return (NULL);
}


int	start_simulation(t_simulation_data *data, t_philo *head)
{
	int			i;

	i = 0;
	// pthread_create(&data->thread, NULL, &data_thread, data);
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
	// pthread_join(data->thread, NULL);
	while ((unsigned long)i > 0)
	{
		pthread_join(head->thread, NULL);
		head = head->left_philo;
		--i;
		printf("joinin\n");
	}
	return (SUCCESS);
}
