/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:39:58 by nammari           #+#    #+#             */
/*   Updated: 2022/01/08 01:38:01 by noufel           ###   ########.fr       */
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

int	wait_for_children(int *pids, unsigned int nb)
{
	unsigned int	i;

	i = 0;
	while (i < nb)
	{
		waitpid(-1, NULL, 0);
		kill_children_process(pids, nb);
		++i;
	}
	return (SUCCESS);
}

int	start_simulation(t_buttler *data, t_philo *philo)
{
	int				*pids;
	unsigned int	i;

	i = 0;
	pids = malloc(sizeof(int) * data->nb_of_philo);
	if (!pids)
		return (ERROR);
	get_time();
	while (i < data->nb_of_philo)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (kill_all(pids, i, ERROR));
		else if (pids[i] == 0)
		{
			free(pids);
			if (philo_process(philo, data, i + 1))
				exit(ERROR);
			exit(SUCCESS);
		}
		++i;
	}
	wait_for_children(pids, data->nb_of_philo);
	free(pids);
	return (SUCCESS);
}

int	close_sem(sem_t *forks, sem_t *print_ts, bool unlink)
{
	sem_close(print_ts);
	sem_close(forks);
	if (unlink)
	{
		sem_unlink(SEM_NAME_PRINT_TS);
		sem_unlink(SEM_NAME_FORKS);
	}
	return (SUCCESS);
}
