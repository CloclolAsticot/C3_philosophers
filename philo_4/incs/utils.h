/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:44:58 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/04 16:29:56 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structures.h"

# define WRONG_FORMAT_NB 4294967295
# define NO_ARG 4294967295

// Input Error messages
# define WRONG_ARG_NB "INPUT ERROR : Wrong number of arguments \
(must be 4 or 5)\n"
# define ARG_NOT_UINT "INPUT ERROR : Wrong argument format \
(arguments must be numbers >= 0 and <= 4294967)\n"
# define ZERO_PHILO "INPUT ERROR : number_of_philosophers must be > 0\n"
# define ZERO_MEAL "INPUT ERROR : If entered - \
number_of_times_each_philosopher_must_eat must be > 0\n"

// Initialization Error messages
# define MALLOC_FAIL "ERROR : Malloc failed\n"
# define MUTEX_FAIL "ERROR : Mutex initialization failed\n"
# define THREAD_CREATION_FAIL "ERROR : Thread creation failed\n"
# define THREAD_JOIN_FAIL "WARNING : Failed to join a thread\n"

// Log messages
# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DEATH_MSG "died"

// Log display

void	print_log(long start_timestamp, long philo_id, char *msg,
			pthread_mutex_t *print_mutex);

bool	protected_print_log(long start_timestamp, long philo_id, char *msg,
			t_data *data);

// Time operations

long	get_current_time_ms(void);

long	get_time_diff_ms(long old_time);

// Clean

void	clean_forks_array(t_fork *forks_array, unsigned int array_size);

void	clean_philos_array(t_philo *philos_array, unsigned int array_size);

void	clean_all(t_philo *philos, t_data *data);

// General Utils

size_t	ft_strlen(const char *str);

void	print_error(char *str);

void	protected_print_error(char *str, pthread_mutex_t *print_mutex);

void	protected_bool_update(bool *bool_to_update, bool updated_value,
			pthread_mutex_t *bool_mutex);

#endif