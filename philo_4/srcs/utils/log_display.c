/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:59:56 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/24 16:22:22 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include <stdio.h>

bool print_log(long timestamp, long philo_id, char *msg, t_data *data)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %ld %s\n", timestamp, philo_id, msg);
	pthread_mutex_unlock(&data->print_mutex);
	return (true);	//the log has been printed
}

bool protected_print_log(long timestamp, long philo_id, char *msg, t_data *data)
{
	pthread_mutex_lock(&data->stop_sim_mutex);
	if (data->stop_sim == true)
	{
		pthread_mutex_unlock(&data->stop_sim_mutex);
		return (false);	//the log has not been printed
	}
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %ld %s\n", timestamp, philo_id, msg);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_unlock(&data->stop_sim_mutex);
	return (true);	//the log has been printed
}

