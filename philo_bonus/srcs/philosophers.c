/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:14:58 by nammari           #+#    #+#             */
/*   Updated: 2022/01/08 01:27:08 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// This two functions are used during corrections to prevent processes from
// running indefinetly

// void	suicide(int signal)
// {
// 	(void)signal;
// 	printf("Child with id %d and parent %d is getting killed \n", getpid(), getppid());
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

static int	init_philosopher(t_buttler *data, t_philo *philo)
{
	data->philo = philo;
	philo->buttler = data;
	philo->last_ate_at = 0;
	philo->nb_time_ate = 0;
	return (SUCCESS);
}

void	kill_children_process(int pids[], unsigned int nb)
{
	unsigned int	i;

	i = 0;
	while (i < nb)
	{
		kill(pids[i], SIGKILL);
		++i;
	}
}

int	main(int argc, char **argv)
{
	t_buttler			data;
	t_philo				philo;
	
	if (parse_input(argc, argv, &data))
		return (ERROR);
	sem_unlink(SEM_NAME_PRINT_TS);
	sem_unlink(SEM_NAME_FORKS);
	philo.fork = sem_open(SEM_NAME_FORKS, O_CREAT, 0666, data.nb_of_philo);
	data.print_ts = sem_open(SEM_NAME_PRINT_TS, O_CREAT, 0666, 1);
	if (philo.fork == SEM_FAILED || data.print_ts == SEM_FAILED)
		return (error_message(SEMAPHORE_CREATION));
	close_sem(data.print_ts, philo.fork, false);
	if (init_philosopher(&data, &philo))
		return (ERROR);
	if (start_simulation(&data, &philo))
		return (ERROR);
	close_sem(data.print_ts, philo.fork, true);
	exit(SUCCESS);
	return (SUCCESS);
}
