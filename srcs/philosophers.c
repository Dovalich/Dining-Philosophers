/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:14:58 by nammari           #+#    #+#             */
/*   Updated: 2021/12/08 11:30:40 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_time(t_simulation_data *data)
{
	struct timeval	time_struct;

	if (gettimeofday(&time_struct, NULL) == -1)
	{
		printf("There was an error with Gettimeofday\n");
		return (ERROR);
	}
	data->starting_time = time_struct.tv_usec;
	return (SUCCESS);
}

int	launch_simulation(t_simulation_data *data)
{
	printf("This is the date of the start %ld\n", data->starting_time);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_simulation_data data;
	(void)argv;
	
	if (argc > 5)
		return (ERROR);
	//if (parse_input())
	//	return (1);
	if (init_time(&data))
		return (ERROR);
	if (launch_simulation(&data))
		return (ERROR);
	return (SUCCESS);
}