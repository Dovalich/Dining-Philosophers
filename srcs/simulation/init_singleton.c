/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_singleton.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:34:20 by nammari           #+#    #+#             */
/*   Updated: 2021/12/17 11:37:55 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_simulation_data	*get_data(void)
{
	static t_simulation_data	*data = NULL;

	if (data == NULL)
	{
		data = malloc(sizeof(t_simulation_data));
		if (data == NULL)
			return (NULL);
	return (data);
}
