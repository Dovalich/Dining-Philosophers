/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:13:19 by nammari           #+#    #+#             */
/*   Updated: 2022/01/07 22:03:21 by noufel           ###   ########.fr       */
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
	(void)signal;
	printf("Child with id %d and parent %d is getting killed \n", getpid(), getppid());
	kill(getpid(), SIGKILL);
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
	buttler->end_simulation = sem_open(SEM_NAME_END, 0);
	if (philo->fork == SEM_FAILED || buttler->print_ts == SEM_FAILED || buttler->end_simulation == SEM_FAILED)
		return (error_message(SEMAPHORE_CREATION));
	philo->id = id;
	if (pthread_create(&buttler->thread, NULL, &buttler_thread, (void *)buttler) == -1)
		return (error_message(THREAD_CREATION));
	while (!buttler->is_end)
	{
		start_eating(philo, buttler);
		start_sleeping(philo, buttler);
		print_status(THINKING, philo);
		usleep(100);
	}
	sem_close(philo->fork);
	sem_close(buttler->end_simulation);
	sem_close(buttler->print_ts);
	return (SUCCESS);
}
