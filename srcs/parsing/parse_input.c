/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:39:40 by nammari           #+#    #+#             */
/*   Updated: 2021/12/08 16:30:42 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_input(int argc, char **argv, t_simulation_data *data)
{
	int	i;

	i = 0;
	if (argc == 1)
		return (ERROR);
	if (!(argc == 5 || argc == 6) || argv == NULL || *argv == NULL)
		return (error_message(PROMPT_USER_INPUT));
	data->has_nb_time_to_eat = true;
	data->nb_of_philo = 5;
	data->nb_time_to_eat = 1;
	data->starting_time = 10;
	data->time_to_die = 20;
	data->time_to_eat = 30;
	data->time_to_sleep = 40;
	return (SUCCESS);
}