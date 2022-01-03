/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:39:58 by nammari           #+#    #+#             */
/*   Updated: 2022/01/03 15:04:30 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_thread(void *philosopher)
{
	t_philo *philo;
	
	// Start of the critical section
	philo = (t_philo *)philosopher;
	while (!philo->data->is_dead)
	{
		start_eating(philo, philo->data);
		if (is_dead(philo, philo->data))
			break ;
		start_sleeping(philo, philo->data);
		if (is_dead(philo, philo->data))
			break ;
		start_thinking(philo, philo->data);
	}
	// end of the critical section
	printf("returning now\n");
	return (NULL);
}

bool	all_philos_alive(t_philo *head, t_simulation_data *data)
{
	t_philo	*head_ptr;

	head_ptr = head;
	while (head->right_philo != head_ptr)
	{
		if (is_dead(head, data))
		{
			pthread_mutex_lock(&data->ts_print);
			printf("%03llu ms Philosopher [%lu] died\n",\
				data->curr_time, head->philo_nb);
			data->is_dead = true;
			pthread_mutex_unlock(&data->ts_print);
			return (false);
		}
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
	while (all_philos_alive(d->philo_lst, d))
	{
		usleep(100);
		update_time(data);
	}
	i = 0;
	d->is_dead = true;
	// while (i < d->nb_of_philo)
	// {
	// 	pthread_join(philo->thread, NULL);
	// 	philo = philo->right_philo;
	// 	++i;
	// }
	return (NULL);
}

int	start_odd(t_philo *head, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&head->thread, NULL, &philo_thread, (void *)head) != 0)
		{
			printf("Pthread_create faillure at Philosopher nb #%lu\n", head->philo_nb);
		}
		i += 2;
		if (head->right_philo != NULL && head->right_philo->right_philo)
			head = head->right_philo->right_philo;
		else
			return (0);
	}
	return (0);
}

int start_even(t_philo *head, int nb_philo)
{
	int	i;

	i = 1;
	while (i < nb_philo)
	{
		if (pthread_create(&head->thread, NULL, &philo_thread, (void *)head) != 0)
		{
			printf("Pthread_create faillure at Philosopher nb #%lu\n", head->philo_nb);
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
	int		i;
	
	data->is_dead = false;
	ptr = head->right_philo;	
	i = data->nb_of_philo;
	data->curr_time = 0;
	start_even(ptr, data->nb_of_philo);
	usleep(1000);
	start_odd(head, data->nb_of_philo);
	pthread_create(&data->thread, NULL, &data_thread, data);
	pthread_join(data->thread, NULL);
	while ((unsigned long)i > 0)
	{
		pthread_join(head->thread, NULL);
		head = head->left_philo;
		--i;
		printf("joinin\n");
	}
	return (SUCCESS);
}
