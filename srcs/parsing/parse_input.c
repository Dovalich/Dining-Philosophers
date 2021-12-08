/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:39:40 by nammari           #+#    #+#             */
/*   Updated: 2021/12/08 16:37:22 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_nb_of_philosophers(char **str, t_simulation_data *data)
{
	//check if is num
	//check if unsigned long (strlen)
	//get_number_using Atolu (atol unsigned)
	//put_number_in_data
	//return Success
}

int	parse_input(int argc, char **argv, t_simulation_data *data)
{
	int	i;

	if (argc == 1)
		return (ERROR);
	if (!(argc == 5 || argc == 6) || argv == NULL || *argv == NULL)
		return (error_message(PROMPT_USER_INPUT));
	
	if (get_nb_of_philosophers(argv, data) == ERROR)
		return (error_message(PROMPT_USER_INPUT));
	data->has_nb_time_to_eat = true;
	data->nb_time_to_eat = 1;
	data->starting_time = 10;
	data->time_to_die = 20;
	data->time_to_eat = 30;
	data->time_to_sleep = 40;
	return (SUCCESS);
}