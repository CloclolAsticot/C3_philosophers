/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:59:56 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/03 19:08:38 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include <bits/pthreadtypes.h>
#include <stdio.h>
#include "utils.h"

void print_log(long start_timestamp, long philo_id, char *msg, pthread_mutex_t *print_mutex)
{
	pthread_mutex_lock(print_mutex);
	printf("%ld %ld %s\n", get_time_diff_ms(start_timestamp), philo_id, msg);
	pthread_mutex_unlock(print_mutex);
}

bool protected_print_log(long start_timestamp, long philo_id, char *msg, t_data *data)
{
	bool *stop_sim;
	pthread_mutex_t *stop_sim_mutex;
	pthread_mutex_t *print_mutex;
	
	stop_sim = &data->stop_sim;
	stop_sim_mutex = &data->stop_sim_mutex;
	print_mutex = &data->print_mutex;
	pthread_mutex_lock(stop_sim_mutex);
	if (*stop_sim == true)
	{
		pthread_mutex_unlock(stop_sim_mutex);
		return (false);	//the log has not been printed
	}
	pthread_mutex_lock(print_mutex);
	printf("%ld %ld %s\n", get_time_diff_ms(start_timestamp), philo_id, msg);
	pthread_mutex_unlock(print_mutex);
	pthread_mutex_unlock(stop_sim_mutex);
	return (true);	//the log has been printed
}

