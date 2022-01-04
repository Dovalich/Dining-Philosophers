/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:49:22 by nammari           #+#    #+#             */
/*   Updated: 2022/01/04 06:44:50 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	data->is_dead = false;
	data->curr_time = 0;
	return (SUCCESS);
}
