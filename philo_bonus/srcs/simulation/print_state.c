/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 01:39:26 by noufel            #+#    #+#             */
/*   Updated: 2022/01/08 15:15:53 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	digit_len(t_u_timestamp nb)
{
	size_t	i;

	i = 1;
	while (nb / 10)
	{
		nb /= 10;
		++i;
	}
	return (i);
}

static void	copy_int_as_str_to_buffer(t_u_timestamp nb, char **buffer)
{
	size_t	len;
	size_t	offset;

	len = digit_len(nb);
	offset = len;
	while (len)
	{
		(*buffer)[len - 1] = (nb % 10) + '0';
		--len;
		nb /= 10;
	}
	*buffer += offset;
}

static void	copy_str_to_buffer(const char *str, char **buffer)
{
	size_t	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i])
	{
		(*buffer)[i] = str[i];
		++i;
	}
	*buffer += i;
}

static void	buffer_state(const char *str, t_philo *philo, char **buffer)
{
	copy_int_as_str_to_buffer(get_time(), buffer);
	copy_str_to_buffer(" ms philosopher nb ", buffer);
	copy_int_as_str_to_buffer(philo->id, buffer);
	copy_str_to_buffer(str, buffer);
}

void	print_status(int philo_state, t_philo *philo)
{
	const char	*state[6];
	char		*buffer_offset;
	char		buffer[BUFFER_SIZE];

	if (sem_wait(philo->buttler->print_ts) == -1)
		exit (0);
	buffer_offset = buffer;
	memset(buffer, 0, BUFFER_SIZE);
	state[SLEEPING] = " is sleeping\n";
	state[THINKING] = " is thinking\n";
	state[EATING] = " is eating\n";
	state[DIED] = " is dead\n";
	state[TOOK_LEFT_FORK] = " took left fork\n";
	state[TOOK_RIGHT_FORK] = " took right fork\n";
	if (philo_state == TOOK_FORKS)
	{
		buffer_state(state[TOOK_LEFT_FORK], philo, &buffer_offset);
		buffer_state(state[TOOK_RIGHT_FORK], philo, &buffer_offset);
	}
	else
		buffer_state(state[philo_state], philo, &buffer_offset);
	write(1, buffer, ft_strlen(buffer));
	if (philo_state != DIED)
		sem_post(philo->buttler->print_ts);
}
