/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:14:58 by nammari           #+#    #+#             */
/*   Updated: 2022/01/08 15:59:40 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// This two functions are used during corrections to prevent processes from
// running indefinetly

// void	suicide(int signal)
// {
// 	(void)signal;
// 	printf("Child with id %d and parent %d is 
//  getting killed \n", getpid(), getppid());
// 	kill(getpid(), SIGKILL);
// }

// void	kill_handler(int signal)
// {
// 	int	parent_pid;
// 	int	i;

// 	parent_pid = getpid();
// 	i = 0;
// 	(void)signal;
// 	while (i < number_of_philo)
// 	{
// 		printf("Killing child with pid %d\n", parent_pid + i + 1);
// 		kill(parent_pid + i + 1, SIGKILL);
// 		++i;
// 	}
// }

static void	unlink_all(void)
{
	sem_unlink(SEM_NAME_PRINT_TS);
	sem_unlink(SEM_NAME_FORKS);
	sem_unlink(SEM_NAME_DEATH);
}

static int	init_philosopher(t_buttler *data, t_philo *philo)
{
	data->philo = philo;
	philo->buttler = data;
	philo->last_ate_at = 0;
	philo->nb_time_ate = 0;
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_buttler			data;
	t_philo				philo;

	if (parse_input(argc, argv, &data))
		return (ERROR);
	unlink_all();
	philo.fork = sem_open(SEM_NAME_FORKS, O_CREAT, 0666, data.nb_of_philo);
	data.print_ts = sem_open(SEM_NAME_PRINT_TS, O_CREAT, 0666, 1);
	data.death = sem_open(SEM_NAME_DEATH, O_CREAT, 0666, 0);
	if (philo.fork == SEM_FAILED || data.print_ts == SEM_FAILED
		|| data.death == SEM_FAILED)
		return (error_message(SEMAPHORE_CREATION));
	close_sem(data.print_ts, philo.fork, false);
	if (init_philosopher(&data, &philo))
		return (ERROR);
	if (start_simulation(&data, &philo))
		return (ERROR);
	close_sem(data.print_ts, philo.fork, true);
	sem_close(data.death);
	sem_unlink(SEM_NAME_DEATH);
	exit(SUCCESS);
	return (SUCCESS);
}
