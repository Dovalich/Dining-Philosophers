/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:14:58 by nammari           #+#    #+#             */
/*   Updated: 2022/01/06 19:55:36 by nammari          ###   ########.fr       */
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


# define NB_PHILO 10

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
		printf("I'm child nb %d\n", i);
	return (0);
}

int	main(void)
{
	pid_t	pids[NB_PHILO];
	sem_t	*sem_forks;
	int		i;
	//sem_t	*sem_print_ts;

	sem_forks = sem_open(SEM_NAME_FORKS, O_CREAT, 0777, NB_PHILO);
	if (sem_forks == SEM_FAILED)
		return (_err_(SEM_NAME_FORKS " failed to open"));
	i = 0;
	while (i < NB_PHILO)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			++i;
			routine(i);
		}
	}
	return (SUCCESS);
}
