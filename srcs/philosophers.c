/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:14:58 by nammari           #+#    #+#             */
/*   Updated: 2021/12/17 16:42:12 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	global = 0;

void	*routine(void *mutex)
{
	int	i;

	i = 0;
	while (i < 1000000)
	{
		++i;
		pthread_mutex_lock(mutex);
		global++;
		pthread_mutex_unlock(mutex);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_simulation_data	data;
	t_philo				*head;
	
	if (parse_input(argc, argv, &data) != SUCCESS)
		return (ERROR);
	head = create_philosopher_linked_list(&data);
	if (head == NULL)
		return (ERROR);
	data.philo_lst = head;
	if (pthread_mutex_init(&data.mutex, NULL) != 0)
		printf("Error init data->mutex\n");
	if (init_time(&data))
		return (ERROR);
	if (start_simulation(&data, head))
		return (ERROR);
	return (SUCCESS);
}
