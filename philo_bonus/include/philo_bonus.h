/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:12:07 by nammari           #+#    #+#             */
/*   Updated: 2022/01/07 22:02:49 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H

# define PHILOSOPHERS_BONUS_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "../custom_library/includes/utils_lib.h"
# include <signal.h>

// Error Enum & Defines ---------------------------------------------------- // 

# define SUCCESS 0
# define ERROR 1
# define BUFFER_SIZE 128
# define SEM_NAME_FORKS "forks"
# define SEM_NAME_PRINT_TS "print_ts"
# define SEM_NAME_END "end_simulation"

typedef unsigned long long u_timestamp;

enum error_flags {
	THREAD_CREATION = 0,
	EMPTY_LIST,
	EMPTY_ELEM,
	INVALID_NB_ARGS,
	PROMPT_USER_INPUT,
	SEMAPHORE_CREATION,
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
typedef struct s_philo t_philo;

typedef struct s_buttler {
	u_timestamp		time_to_die;
	u_timestamp		time_to_eat;
	u_timestamp		time_to_sleep;
	sem_t			*print_ts;
	sem_t			*end_simulation;
	pthread_t		thread;
	unsigned long	nb_of_philo;
	unsigned long	nb_time_to_eat;
	bool			is_end;
	t_philo			*philo;
}				t_buttler;

typedef struct s_philo {
	pid_t				pid;
	unsigned long		id;
	unsigned long		nb_time_ate;
	u_timestamp			last_ate_at;
	sem_t				*fork;
	t_buttler			*buttler;
}				t_philo;

// ------------------------------------------------------------------------ //

// Functions Prototypes --------------------------------------------------- //

	// Error_Management

int				error_message(int error_type);
void			*malloc_error(char *error_msg);
void			free_list(t_philo *head);
void			*mutex_creation_error(void);

	
	// Parsing

int				parse_input(int argc, char **argv, t_buttler *data);
int				get_nb_of_philosophers(char *argv, t_buttler *data);
int				get_time_to_die(char *argv, t_buttler *data);
int				get_time_to_eat(char *argv, t_buttler *data);
int				get_time_to_sleep(char *argv, t_buttler *data);
int				get_nb_times_to_eat(char *argv, t_buttler *data);

	// Simulation

void			*buttler_thread(void *data);
u_timestamp		get_time(void);
int				start_simulation(t_buttler *data, t_philo *head);
int				terminate_simulation(t_buttler *data, t_philo *philo);
void			print_status(int philo_state, t_philo *philo);
void			custom_usleep(u_timestamp sleep_for);
int				philo_process(t_philo *philo, t_buttler *buttler, int id);
void			suicide(int signal);

// ---------------------------------------------------------------------- //

#endif