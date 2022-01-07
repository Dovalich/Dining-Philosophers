/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:39:58 by nammari           #+#    #+#             */
/*   Updated: 2022/01/07 23:42:27 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	kill_all(int *pids, int index, int return_status)
{
	while (index > 0)
	{
		kill(pids[index], SIGKILL);
		--index;
	}
	return (return_status);
}

int	start_simulation(t_buttler *data, t_philo *philo)
{
	int				pids[data->nb_of_philo];
	unsigned int	i;

	i = 0;
	get_time();
	while (i < data->nb_of_philo)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (kill_all(pids, i, ERROR));
		else if (pids[i] == 0)
		{
			signal(SIGINT, &suicide);
			if (philo_process(philo, data, i + 1))
				exit(ERROR);
			exit(SUCCESS);
		}
		++i;
	}
	while (i > 0)
	{
		waitpid(-1, NULL, 0);
		kill_children_process(pids, data->nb_of_philo);
		--i;
	}
	return (SUCCESS);
}

// int	terminate_simulation(t_buttler *data, t_philo *philo)
// {
// 	unsigned long	i;

// 	pthread_join(data->thread, NULL);
// 	pthread_mutex_destroy(&data->ts_print);
// 	i = 0;
// 	while ((unsigned long)i < data->nb_of_philo)
// 	{
// 		pthread_join(philo_lst[i].thread, NULL);
// 		pthread_mutex_destroy(&philo_lst[i].forks[i]);
// 		++i;
// 	}
// 	free(philo_lst->forks);
// 	free(philo_lst);
// 	return (SUCCESS);
// }
