/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_test_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:56:24 by nammari           #+#    #+#             */
/*   Updated: 2021/12/16 14:38:36 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_list(t_philo *head, t_simulation_data *data)
{
	unsigned long		i;
	
	i = 0;
	if (head == NULL)
		printf("List is Empty.\n");
	else if (data->nb_of_philo == 1)
	{
		printf("This is Philo nb #%0lu. To my Left Philo_nb #%p and to My Right Philo_nb #%p\n", head->id, head->left_philo, head->right_philo);
	}
	else
	{
		while (i < data->nb_of_philo) 
		{
			++i;
			printf("This is Philo nb #%0lu. To my Left Philo_nb #%0lu and to My Right Philo_nb #%0lu\n", head->id, head->left_philo->id, head->right_philo->id);
			head = head->right_philo;
		}
	}
}
