/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosopher_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:33:55 by nammari           #+#    #+#             */
/*   Updated: 2021/12/17 11:52:16 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_new_elem(t_simulation_data *data, unsigned long philo_nb)
{
	t_philo	*new;

	new = (t_philo*)malloc(sizeof(t_philo));
	if (new == NULL)
		return (malloc_error("Create_new_elem malloc failed\n"));
	new->left_philo = NULL;
	new->right_philo = NULL;
	new->philo_nb = philo_nb;
	new->time_to_die = data->time_to_die;
	new->time_to_eat = data->time_to_eat;
	new->time_to_sleep = data->time_to_sleep;
	if (data->has_nb_time_to_eat)
		new->nb_time_to_eat = data->nb_time_to_eat;
	else
		new->nb_time_to_eat = ULONG_MAX;
	return (new);
}

int	elem_push_back(t_philo **head, t_philo *elem)
{
	t_philo	*current;

	if (elem == NULL)
		return (EMPTY_ELEM);
	else if (head == NULL)
		return (error_message(EMPTY_LIST));
	else if (*head == NULL)
		*head = elem;
	else
	{
		current = *head;
		while (current->right_philo != NULL && current->right_philo != *head)
			current = current->right_philo;
		current->right_philo = elem;
		elem->right_philo = *head;
		elem->left_philo = current;
		(*head)->left_philo = elem;
	}
	return (SUCCESS);
}

t_philo	*create_philosopher_linked_list(t_simulation_data *data)
{
	t_philo			*head;
	unsigned int	i;
	 
	i = 0;
	head = NULL;
	while (i < data->nb_of_philo)
	{
		if (elem_push_back(&head, create_new_elem(data, i + 1)) != SUCCESS)
		{
			free_list(head);
			printf("Error: Malloc faillure on""\
					 create_philosopher_linked_list\n");
			return (NULL);
		}
		++i;
	}
	return (head);
}

