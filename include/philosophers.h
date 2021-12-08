/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:12:07 by nammari           #+#    #+#             */
/*   Updated: 2021/12/08 15:38:00 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

// Error Enum & Defines ---------------------------------------------------- // 

# define SUCCESS 0
# define ERROR 1

enum error_flags {
	THREAD_CREATION = 2,
	EMPTY_LIST,
	EMPTY_ELEM,
};

// Structures ------------------------------------------------------------- //

typedef struct s_simulation_data {
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	nb_of_philo;
	unsigned long	starting_time;
	unsigned long	nb_time_to_eat;
	bool			has_nb_time_to_eat;
}				t_simulation_data;

typedef struct s_philo {
	unsigned long	philo_nb;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	nb_time_to_eat;
	bool			has_nb_time_to_eat;
	struct s_philo	*left_philo;
	struct s_philo	*right_philo;
}				t_philo;

// ------------------------------------------------------------------------ //

// Functions Prototypes --------------------------------------------------- //

	// Error_Management

int		error_message(int error_type);
void	*malloc_error(char *error_msg);
	
	// Parsing
	

	// Simulation
	
void	ft_usleep(int sleep_time);
int		init_time(t_simulation_data *data);
int		launch_simulation(t_simulation_data *data);
t_philo	*create_philosopher_linked_list(t_simulation_data *data);

	// Utils
	
void	ft_putstr_fd(char *str, int fd);
void	free_list(t_philo *head);
// ---------------------------------------------------------------------- //

#endif