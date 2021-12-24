/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:12:07 by nammari           #+#    #+#             */
/*   Updated: 2021/12/24 13:50:41 by nammari          ###   ########.fr       */
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
# include "../custom_library/includes/utils_lib.h"

// Error Enum & Defines ---------------------------------------------------- // 

# define SUCCESS 0
# define ERROR 1

enum error_flags {
	THREAD_CREATION = 2,
	EMPTY_LIST,
	EMPTY_ELEM,
	INVALID_NB_ARGS,
	PROMPT_USER_INPUT,
};

// Structures ------------------------------------------------------------- //

typedef struct s_simulation_data {
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	nb_of_philo;
	unsigned long	starting_time;
	unsigned long	nb_time_to_eat;
	unsigned long	curr_time;
	bool			has_nb_time_to_eat;
	bool			is_dead;
	pthread_mutex_t	ts_print;
	pthread_t		thread;
	struct timeval	tv;
	struct s_philo	*philo_lst;
}				t_simulation_data;

typedef struct s_philo {
	unsigned long		philo_nb;
	unsigned long		last_ate_at;
	unsigned long		nb_time_to_eat;
	bool				is_eating;
	bool				is_thinking;
	bool				is_sleeping;
	bool				is_alive;
	bool				fork_on_table;
	pthread_mutex_t		fork;
	pthread_t			thread;
	t_simulation_data	*data;
	struct s_philo		*left_philo;
	struct s_philo		*right_philo;
}				t_philo;

// ------------------------------------------------------------------------ //

// Functions Prototypes --------------------------------------------------- //

	// Error_Management

int				error_message(int error_type);
void			*malloc_error(char *error_msg);
void			free_list(t_philo *head);
void			*mutex_creation_error(void);

	
	// Parsing

int				parse_input(int argc, char **argv, t_simulation_data *data);
int				get_nb_of_philosophers(char *argv, t_simulation_data *data);
int				get_time_to_die(char *argv, t_simulation_data *data);
int				get_time_to_eat(char *argv, t_simulation_data *data);
int				get_time_to_sleep(char *argv, t_simulation_data *data);
int				get_nb_times_to_eat(char *argv, t_simulation_data *data);

	// Simulation

unsigned long	get_time(t_simulation_data *data);
void			ft_usleep(int sleep_time);
int				init_time(t_simulation_data *data);
void			update_time(t_simulation_data *data);
int				start_simulation(t_simulation_data *data, t_philo *head);
t_philo			*create_philosopher_linked_list(t_simulation_data *data);
void			print_state(t_philo *philo);
void			start_sleeping(t_philo *philo, t_simulation_data *data);
void			start_eating(t_philo *philo, t_simulation_data *data);
void			start_thinking(t_philo *philo, t_simulation_data *data);

void			print_took_forks(t_philo *philo);

	// Utils


	// Testing -> To be deleted before pushing

void			print_list(t_philo *head, t_simulation_data *data);
// ---------------------------------------------------------------------- //

#endif