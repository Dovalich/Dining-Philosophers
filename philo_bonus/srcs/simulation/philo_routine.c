/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:13:19 by nammari           #+#    #+#             */
/*   Updated: 2022/01/08 16:00:03 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	start_eating(t_philo *philo, t_buttler *buttler)
{
	if (sem_wait(philo->fork) == -1 || sem_wait(philo->fork) == -1)
		return ;
	philo->last_ate_at = get_time();
	print_status(TOOK_FORKS, philo);
	print_status(EATING, philo);
	philo->nb_time_ate += 1;
	custom_usleep(buttler->time_to_eat);
	if (sem_post(philo->fork) == -1 || sem_post(philo->fork) == -1)
		return ;
}

static void	start_sleeping(t_philo *philo, t_buttler *buttler)
{
	print_status(SLEEPING, philo);
	custom_usleep(buttler->time_to_sleep);
}

void	*buttler_thread(void *data)
{
	t_buttler	*buttler;

	buttler = (t_buttler *)data;
	while (!buttler->is_end)
	{
		if (get_time() - buttler->philo->last_ate_at >= buttler->time_to_die)
		{
			print_status(DIED, buttler->philo);
			sem_post(buttler->death);
			buttler->is_end = true;
			close_sem(buttler->print_ts, buttler->philo->fork, true);
			exit(0);
		}
		usleep(1000);
	}
	return (NULL);
}

static int	init_philo_process(t_philo *philo, int id, t_buttler *buttler)
{
	philo->id = id;
	philo->fork = sem_open(SEM_NAME_FORKS, 0);
	buttler->print_ts = sem_open(SEM_NAME_PRINT_TS, 0);
	buttler->death = sem_open(SEM_NAME_DEATH, 0);
	if (philo->fork == SEM_FAILED || buttler->print_ts == SEM_FAILED
		|| buttler->death == SEM_FAILED)
		return (error_message(SEMAPHORE_CREATION));
	if (pthread_create(&buttler->thread, NULL, &buttler_thread, buttler))
		return (error_message(THREAD_CREATION));
	pthread_detach(buttler->thread);
	return (SUCCESS);
}

int	philo_process(t_philo *philo, t_buttler *buttler, int id)
{
	if (init_philo_process(philo, id, buttler))
		exit(ERROR);
	while (!buttler->is_end)
	{
		if (philo->nb_time_ate == buttler->nb_time_to_eat)
		{
			sem_wait(buttler->print_ts);
			write(1, "Game Ended\n", 11);
			break ;
		}
		start_eating(philo, buttler);
		start_sleeping(philo, buttler);
		print_status(THINKING, philo);
		usleep(100);
	}
	sem_post(buttler->death);
	close_sem(buttler->print_ts, philo->fork, true);
	return (SUCCESS);
}
