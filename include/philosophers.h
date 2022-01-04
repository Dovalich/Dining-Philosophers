/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:12:07 by nammari           #+#    #+#             */
/*   Updated: 2022/01/04 16:18:13 by noufel           ###   ########.fr       */
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
# define BUFFER_SIZE 128

typedef unsigned long long u_timestamp;

enum error_flags {
	THREAD_CREATION = 0,
	EMPTY_LIST,
	EMPTY_ELEM,
	INVALID_NB_ARGS,
	PROMPT_USER_INPUT,
};

typedef enum philo_states {
	SLEEPING = 0,
	THINKING,
	EATING,
	DIED,
	TOOK_LEFT_FORK,
	TOOK_RIGHT_FORK,
	TOOK_FORKS
} 			philo_states;

// Structures ------------------------------------------------------------- //

typedef struct s_simulation_data {
	u_timestamp		time_to_die;
	u_timestamp		time_to_eat;
	u_timestamp		time_to_sleep;
	pthread_mutex_t	ts_print;
	pthread_t		thread;
	unsigned long	nb_of_philo;
	unsigned long	nb_time_to_eat;
	bool			is_end;
	struct s_philo	*philo_lst;
}				t_simulation_data;

typedef struct s_philo {
	unsigned long		id;
	unsigned long		nb_time_ate;
	u_timestamp			last_ate_at;
	pthread_mutex_t		*forks;
	pthread_t			thread;
	t_simulation_data	*data;
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

u_timestamp		get_time(void);
void			*philo_thread(t_philo *philo);
void			*data_thread(void *data);
int				start_simulation(t_simulation_data *data, t_philo *head);
int				terminate_simulation(t_simulation_data *data, t_philo *philo);
void			print_status(int philo_state, t_philo *philo);
void			custom_usleep(u_timestamp sleep_for);

	// Testing -> To be deleted before pushing

void			print_list(t_philo *head, t_simulation_data *data);
// ---------------------------------------------------------------------- //

#endif