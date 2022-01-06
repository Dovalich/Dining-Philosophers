/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:14:58 by nammari           #+#    #+#             */
/*   Updated: 2022/01/06 20:55:36 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static t_philo	*init_philosophers(t_simulation_data *data)
// {
// 	pthread_mutex_t	*forks;
// 	t_philo			*philo_list;
// 	unsigned int	i;
	
// 	forks = malloc(sizeof(*forks) * data->nb_of_philo);
// 	philo_list = malloc(sizeof(*philo_list) * data->nb_of_philo);
// 	if (forks == NULL || philo_list == NULL)
// 		return (malloc_error("Failed malloc\n"));
// 	data->philo_lst = philo_list;
// 	i = 0;
// 	while (i < data->nb_of_philo)
// 	{
// 		philo_list[i].id = i + 1;
// 		philo_list[i].last_ate_at = 0;
// 		philo_list[i].nb_time_ate = 0;
// 		philo_list[i].forks = forks;
// 		philo_list[i].data = data;
// 		pthread_mutex_init(&forks[i], NULL);
// 		++i;
// 	}
// 	return (philo_list);
// }


# define NB_PHILO 2

int	_err_(char *str)
{
	printf("%s\n", str);
	return (ERROR);
}

int	routine(int	i)
{
	sem_t	*sem_fork;

	sem_fork = sem_open(SEM_NAME_FORKS, 0);
	if (sem_fork == SEM_FAILED)
		return (_err_("Sem failed in child"));
	else
	{
		printf("I'm child nb %d doing my work...\n", i);
		sem_wait(sem_fork);
		printf("inside sem_wait\n");
		sleep(2);
		sem_post(sem_fork);
	}
	return (0);
}

int	main(void)
{
	pid_t	pids[NB_PHILO];
	sem_t	*sem_forks;
	int		i;

	sem_forks = sem_open(SEM_NAME_FORKS, O_CREAT, S_IRUSR | S_IWUSR, 0);
	if (sem_forks == SEM_FAILED)
		return (_err_(SEM_NAME_FORKS " failed to open"));
	i = 0;
	sem_post(sem_forks);
	while (i < NB_PHILO)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			routine(i);
			return (SUCCESS);
		}
		++i;
	}
	i = 0;
	while (i < NB_PHILO)
	{
		waitpid(pids[i], NULL, 0);
		++i;
	}
	printf("I'm main here's my id: %d and i'm terminating\n",getpid());
	return (SUCCESS);
}
