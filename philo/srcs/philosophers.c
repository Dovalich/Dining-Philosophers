/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:14:58 by nammari           #+#    #+#             */
/*   Updated: 2022/01/08 11:37:51 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*init_philosophers(t_simulation_data *data)
{
	pthread_mutex_t	*forks;
	t_philo			*philo_list;
	unsigned int	i;

	forks = malloc(sizeof(*forks) * data->nb_of_philo);
	philo_list = malloc(sizeof(*philo_list) * data->nb_of_philo);
	if (forks == NULL || philo_list == NULL)
		return (malloc_error("Failed malloc\n"));
	data->philo_lst = philo_list;
	i = 0;
	while (i < data->nb_of_philo)
	{
		philo_list[i].id = i + 1;
		philo_list[i].last_ate_at = 0;
		philo_list[i].nb_time_ate = 0;
		philo_list[i].forks = forks;
		philo_list[i].data = data;
		pthread_mutex_init(&forks[i], NULL);
		++i;
	}
	return (philo_list);
}

int	main(int argc, char **argv)
{
	t_simulation_data	data;
	t_philo				*philo_list;

	if (parse_input(argc, argv, &data) != SUCCESS)
		return (ERROR);
	philo_list = init_philosophers(&data);
	if (philo_list == NULL)
		return (ERROR);
	if (pthread_mutex_init(&data.ts_print, NULL) != 0)
		printf("Error init data->mutex\n");
	get_time();
	if (start_simulation(&data, philo_list))
		return (ERROR);
	terminate_simulation(&data, philo_list);
	return (SUCCESS);
}
