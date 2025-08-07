/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:59:56 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/04 16:23:45 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

/**
 * @brief Prints a timestamped log message for a philosopher in a 
 * thread-safe manner.
 * 
 * @param start_timestamp The initial timestamp when the program started 
 * (in milliseconds).
 * @param philo_id The unique identifier of the philosopher.
 * @param msg The message string to be displayed 
 * (e.g., "is eating", "is sleeping").
 * @param print_mutex Pointer to the mutex used to synchronize console
 * output access.
 */
void	print_log(long start_timestamp, long philo_id, char *msg,
		pthread_mutex_t *print_mutex)
{
	pthread_mutex_lock(print_mutex);
	printf("%ld %ld %s\n", get_time_diff_ms(start_timestamp), philo_id, msg);
	pthread_mutex_unlock(print_mutex);
}

/**
 * @brief Safely prints a log message for a philosopher - checks if the 
 * simulation has stopped before printing the log.
 * 
 * @param start_timestamp The timestamp when the simulation started.
 * @param philo_id The unique identifier of the philosopher performing the
 * action.
 * @param msg The message string describing the philosopher's action.
 * @param data Pointer to the shared data structure.
 * 
 * @return true if the message was successfully printed, false if simulation was
 * stopped.
 */
bool	protected_print_log(long start_timestamp, long philo_id, char *msg,
		t_data *data)
{
	bool			*stop_sim;
	pthread_mutex_t	*stop_sim_mutex;
	pthread_mutex_t	*print_mutex;

	stop_sim = &data->stop_sim;
	stop_sim_mutex = &data->stop_sim_mutex;
	print_mutex = &data->print_mutex;
	pthread_mutex_lock(stop_sim_mutex);
	if (*stop_sim == true)
	{
		pthread_mutex_unlock(stop_sim_mutex);
		return (false);
	}
	pthread_mutex_lock(print_mutex);
	printf("%ld %ld %s\n", get_time_diff_ms(start_timestamp), philo_id, msg);
	pthread_mutex_unlock(print_mutex);
	pthread_mutex_unlock(stop_sim_mutex);
	return (true);
}
