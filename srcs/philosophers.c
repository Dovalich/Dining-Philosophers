/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:14:58 by nammari           #+#    #+#             */
/*   Updated: 2021/12/14 12:53:26 by nammari          ###   ########.fr       */
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

int	parse_input(int argc, char **argv, t_simulation_data *data)
{
	if (!(argc == 5 || argc == 6) || argv == NULL || *argv == NULL)
		return (error_message(PROMPT_USER_INPUT));
	if (get_nb_of_philosophers(argv[1], data) == ERROR)
		return (error_message(PROMPT_USER_INPUT));
	if (get_time_to_die(argv[2], data) == ERROR)
		return (error_message(PROMPT_USER_INPUT));
	if (get_time_to_eat(argv[3], data) == ERROR)
		return (error_message(PROMPT_USER_INPUT));
	if (get_time_to_sleep(argv[4], data) == ERROR)
		return (error_message(PROMPT_USER_INPUT));
	if (argv[5])
		if (get_nb_times_to_eat(argv[5], data) == ERROR)
			return (error_message(PROMPT_USER_INPUT));
	return (SUCCESS);
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
	// if (launch_simulation(&data))
	// 	return (ERROR);
	return (SUCCESS);
}
