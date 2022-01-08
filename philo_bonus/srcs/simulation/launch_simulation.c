/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:39:58 by nammari           #+#    #+#             */
/*   Updated: 2022/01/08 15:50:00 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	kill_children_proc(int **pids, unsigned int nb, int status)
{
	unsigned int	i;

	i = 0;
	while (i < nb)
	{
		kill((*pids)[i], SIGKILL);
		++i;
	}
	free(*pids);
	return (status);
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
			return (kill_children_proc(&pids, i, ERROR));
		else if (pids[i] == 0)
		{
			free(pids);
			if (philo_process(philo, data, i + 1))
				exit(ERROR);
			exit(SUCCESS);
		}
		++i;
	}
	sem_wait(data->death);
	return (kill_children_proc(&pids, data->nb_of_philo, SUCCESS));
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
