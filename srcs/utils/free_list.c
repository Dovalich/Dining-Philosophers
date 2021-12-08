/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:35:51 by nammari           #+#    #+#             */
/*   Updated: 2021/12/08 15:35:56 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_list(t_philo *head)
{
	t_philo	*tmp;
	t_philo	*first_philo;

	first_philo = head;
	if (head == NULL)
		return ;
	while (head->right_philo != first_philo)
	{
		tmp = head;
		head = head->right_philo;
		free(tmp);
		tmp = head;
	}
	free(head);
}
