/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:13:19 by nammari           #+#    #+#             */
/*   Updated: 2022/01/07 18:02:45 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock_fork(t_philo *philo)
{
	sem_wait(philo->fork);
	sem_wait(philo->fork);
}

void	unlock_fork(t_philo *philo)
{
	sem_post(philo->fork);
	sem_post(philo->fork);
}

void	start_eating(t_philo *philo, t_buttler *data)
{
	lock_fork(philo);
	philo->last_ate_at = get_time();
	if (data->is_end)
	{
		unlock_fork(philo);
		return ;
	}
	print_status(TOOK_FORKS, philo);
	print_status(EATING, philo);
	philo->nb_time_ate += 1;
	custom_usleep(data->time_to_eat);
	unlock_fork(philo);
}

void	suicide(int signal)
{
	if (signal == SIGQUIT || signal == SIGKILL)
	{
		printf("-++++++++++++++++++++++++++++++CHILD ++++++++\n\n\n\n");
		kill(getpid(), SIGKILL);
	}
}

void	start_sleeping(t_philo *philo, t_buttler *data)
{	
	print_status(SLEEPING, philo);
	custom_usleep(data->time_to_sleep);
}

int	philo_process(t_philo *philo, t_buttler *buttler, int id)
{
	philo->fork = sem_open(SEM_NAME_FORKS, 0);
	buttler->print_ts = sem_open(SEM_NAME_PRINT_TS, 0);
	if (philo->fork == SEM_FAILED || buttler->print_ts == SEM_FAILED)
		return (error_message(SEMAPHORE_CREATION));
	philo->id = id + 1;
	// if (pthread_create(&buttler->thread, NULL, &buttler_thread, buttler) == -1)
		// return (error_message(THREAD_CREATION));
	while (!buttler->is_end)
	{
		start_eating(philo, buttler);
		start_sleeping(philo, buttler);
		print_status(THINKING, philo);
		usleep(100);
		signal(SIGQUIT, &suicide);
	}
	return (SUCCESS);
}
