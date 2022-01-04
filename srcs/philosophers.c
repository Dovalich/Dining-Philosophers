/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:14:58 by nammari           #+#    #+#             */
/*   Updated: 2022/01/04 06:26:10 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_simulation_data	data;
	t_philo				*philo_lst;
	pthread_mutex_t		*forks;
	unsigned int		i;
	
	if (parse_input(argc, argv, &data) != SUCCESS)
		return (ERROR);
	i = 0;
	forks = malloc(sizeof(*forks) * data.nb_of_philo);
	philo_lst = malloc(sizeof(*philo_lst) * data.nb_of_philo);
	data.philo_lst = philo_lst;
	while (i < data.nb_of_philo)
	{
		philo_lst[i].id = i + 1;
		philo_lst[i].is_alive = true;
		philo_lst[i].last_ate_at = 0;
		philo_lst[i].nb_time_to_eat = data.nb_time_to_eat;
		philo_lst[i].forks = forks;
		philo_lst[i].data = &data;
		++i;
	}
	i = 0;
	while (i < data.nb_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		++i;
	}
	if (pthread_mutex_init(&data.ts_print, NULL) != 0)
		printf("Error init data->mutex\n");
	get_time();
	if (start_simulation(&data, philo_lst))
		return (ERROR);
	terminate_simulation(&data, philo_lst);
	// free_list(head);
	return (SUCCESS);
}
