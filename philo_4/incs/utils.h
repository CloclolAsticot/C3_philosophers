/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:44:58 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/24 16:42:47 by csavreux         ###   ########lyon.fr   */
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

void print_log(long timestamp, long philo_id, char *msg, t_data *data);

bool protected_print_log(long timestamp, long philo_id, char *msg, t_data *data);

// Time operations

long	get_current_time_ms(void);

long	get_time_diff_ms(long old_time);

// Clean

void clean_forks_array(t_fork *forks_array, unsigned int array_size);

void clean_philos_array(t_philo *philos_array, unsigned int array_size);

void clean_all(t_philo *philos, t_data * data);

#endif