/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:54:33 by nammari           #+#    #+#             */
/*   Updated: 2021/12/17 12:18:06 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_time(t_simulation_data *data)
{
	if (gettimeofday(&data->tv, NULL) == -1)
	{
		printf("There was an error with Gettimeofday\n");
		return (ERROR);
	}
	data->starting_time = (&data->tv)->tv_usec / 1000;
	return (SUCCESS);
}
