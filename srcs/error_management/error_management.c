/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:38:58 by nammari           #+#    #+#             */
/*   Updated: 2021/12/08 15:26:38 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_message(int error_type)
{
	if (error_type == THREAD_CREATION)
		ft_putstr_fd("Pthread_create failed\n", 2);
	else if (error_type == EMPTY_LIST)
		ft_putstr_fd("Error! Empty list\n", 2);
	else if (error_type == EMPTY_LIST)
		ft_putstr_fd("Error! Pushing NULL Elem to list\n", 2);
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