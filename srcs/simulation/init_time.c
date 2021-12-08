/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:54:33 by nammari           #+#    #+#             */
/*   Updated: 2021/12/08 11:54:46 by nammari          ###   ########.fr       */
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
