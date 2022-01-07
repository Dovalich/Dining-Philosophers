/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:13:19 by nammari           #+#    #+#             */
/*   Updated: 2022/01/07 23:31:20 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	lock_fork(t_philo *philo)
{
	if (sem_wait(philo->fork) == -1 || sem_wait(philo->fork) == -1)
		return ;
}

void	unlock_fork(t_philo *philo)
{
	if (sem_post(philo->fork) == -1 || sem_post(philo->fork) == -1)
		return ;
}

void	start_eating(t_philo *philo, t_buttler *data)
{
	lock_fork(philo);
	philo->last_ate_at = get_time();
	print_status(TOOK_FORKS, philo);
	print_status(EATING, philo);
	philo->nb_time_ate += 1;
	custom_usleep(data->time_to_eat);
	unlock_fork(philo);
}

void	suicide(int signal)
{
	(void)signal;
	printf("Child with id %d and parent %d is getting killed \n", getpid(), getppid());
	kill(getpid(), SIGKILL);
}

void	start_sleeping(t_philo *philo, t_buttler *data)
{	
	print_status(SLEEPING, philo);
	custom_usleep(data->time_to_sleep);
}

void	*buttler_thread(void *dat)
{
	t_buttler	*data;

	data = (t_buttler *)dat;
	while (!data->is_end)
	{
		if (get_time() - data->philo->last_ate_at >= data->time_to_die)
		{
			print_status(DIED, data->philo);
			data->is_end = true;
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

int	philo_process(t_philo *philo, t_buttler *buttler, int id)
{
	philo->fork = sem_open(SEM_NAME_FORKS, 0);
	buttler->print_ts = sem_open(SEM_NAME_PRINT_TS, 0);
	if (philo->fork == SEM_FAILED || buttler->print_ts == SEM_FAILED)
		return (error_message(SEMAPHORE_CREATION));
	philo->id = id;
	if (pthread_create(&buttler->thread, NULL, &buttler_thread, (void *)buttler) == -1)
		return (error_message(THREAD_CREATION));
	while (!buttler->is_end)
	{
		if (philo->nb_time_ate == buttler->nb_time_to_eat)
		{
			sem_wait(buttler->print_ts);
			write(1, "Game Ended\n", 11);
			buttler->is_end = true;
			break ;
		}
		if (!buttler->is_end)
			break ;
		start_eating(philo, buttler);
		if (!buttler->is_end)
			break ;
		start_sleeping(philo, buttler);
		if (!buttler->is_end)
			break ;
		print_status(THINKING, philo);
		if (!buttler->is_end)
			break ;
		usleep(100);
	}
	pthread_join(buttler->thread, NULL);
	exit(0);
	return (SUCCESS);
}
