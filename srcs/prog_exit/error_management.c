/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:38:58 by nammari           #+#    #+#             */
/*   Updated: 2021/12/23 11:11:19 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_message(int error_type)
{
	if (error_type == THREAD_CREATION)
		ft_putstr_fd("Error! Pthread_create failed\n", 2);
	else if (error_type == EMPTY_LIST)
		ft_putstr_fd("Error! Empty list\n", 2);
	else if (error_type == EMPTY_LIST)
		ft_putstr_fd("Error! Pushing NULL Elem to list\n", 2);
	else if (error_type == INVALID_NB_ARGS)
		ft_putstr_fd("Error! Invalid number of arguments\n", 2);
	else if (error_type == PROMPT_USER_INPUT)
	{
		ft_putstr_fd("The program should take the following arguments:\n\n", 2);
		ft_putstr_fd("number_of_philosophers ", 2);
		ft_putstr_fd("time_to_die time_to_eat time_to_sleep ", 2);
		ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n", 2);
	}
	return (ERROR);
}

void	*malloc_error(char *error_msg)
{
	if (error_msg == NULL)
	{
		ft_putstr_fd("Error\n", 2);
	}
	else
	{
		ft_putstr_fd(error_msg, 2);
	}
	return (NULL);
}

void	*mutex_creation_error(void)
{
	printf("Mutex_init_failed at Philosopher\n");
	return (NULL);
}