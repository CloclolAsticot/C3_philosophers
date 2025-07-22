/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:44:58 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/22 14:17:00 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structures.h"

# define WRONG_FORMAT 4294967295
# define NO_ARG 4294967295

// Log messages
# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DEATH_MSG "died"

// Log display
void	protected_log_print(unsigned int timestamp, unsigned int philo_id,
			char *msg, t_config *config);

void	protected_print(char *msg, t_config *config);

// Time operations
long	get_current_time_ms(void);

long	get_time_diff_ms(long old_time);

// Safe bool operations
bool	protected_bool_check(bool bool_value, pthread_mutex_t bool_mutex);

void	protected_bool_update(bool *bool_to_update, bool updated_value,
			pthread_mutex_t bool_mutex);

// Cleaning functions
void	clean_forks_array(t_fork *forks_array, unsigned int array_size);

void	clean_philos_array(t_philo *philos_array, unsigned int array_size);

void	clean_all(t_philo *philos, t_config *config);

#endif