/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:14:58 by nammari           #+#    #+#             */
/*   Updated: 2021/12/17 12:18:20 by nammari          ###   ########.fr       */
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

int	get_time(t_simulation_data *data)
{	
	unsigned long	cur_time;
	
	gettimeofday(&data->tv, NULL);
	cur_time = data->tv.tv_usec / 1000;
	printf("Time to run your function is %lu ms\n", 
			cur_time - data->starting_time);
	return (0);
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
	print_list(head, &data);
	if (init_time(&data))
		return (ERROR);
	if (launch_simulation(&data, head))
		return (ERROR);
	return (SUCCESS);
}
