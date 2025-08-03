/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:32:59 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/03 15:53:13 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "threads_handling.h"
#include "utils.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void	terminate_philos_threads(t_philo *philos, unsigned int nb_of_threads,
		t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < nb_of_threads)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("Warning: Failed to join philos[%u]'s thread\n", i);
			pthread_mutex_unlock(&data->print_mutex);
		}
		i++;
	}
}

void	terminate_all_threads(t_philo *philos, unsigned int nb_of_philo_threads, pthread_t *monitor,
		t_data *data)
{
	unsigned int	i;

	i = 0;
	if (pthread_join(*monitor, NULL) != 0)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("Warning: Failed to join monitor thread\n");
		pthread_mutex_unlock(&data->print_mutex);
	}
	while (i < nb_of_philo_threads)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("Warning: Failed to join philos[%u]'s thread\n", i);
			pthread_mutex_unlock(&data->print_mutex);
		}
		i++;
	}
}

static void	thread_creation_failure_cleanup(t_philo *philos,
		unsigned int nb_of_philo_threads, t_data *data)
{
	pthread_mutex_lock(&data->stop_sim_mutex);
	data->stop_sim = true;
	pthread_mutex_unlock(&data->stop_sim_mutex);
	terminate_philos_threads(philos, nb_of_philo_threads, data);
	clean_all(philos, data);
}

void	*create_philo_threads(t_philo *philos, unsigned int nb_of_philos,
		t_data *data)
{
	unsigned int	i;

	int thread_creation_return ;
	i = 0;
	while (i < nb_of_philos)
	{
		if (philos[i].id % 2 == 0)
			thread_creation_return = pthread_create(&philos[i].thread_id, NULL,
					&philo_routine_even, &philos[i]);
		else
			thread_creation_return = pthread_create(&philos[i].thread_id, NULL,
					&philo_routine_odd, &philos[i]);
		if (thread_creation_return != 0)
		{
			thread_creation_failure_cleanup(philos, i, data);
			pthread_mutex_lock(&data->print_mutex);
			printf("Error : Thread creation failure for philos[%u]\n", i);
			pthread_mutex_unlock(&data->print_mutex);
			return (NULL);
		}
		i++;
	}
	return (philos);
}

void	*create_monitor_thread(pthread_t *monitor, t_philo *philos,
		t_data *data)
{
	if (pthread_create(monitor, NULL, &monitor_routine, philos) != 0)
	{
		thread_creation_failure_cleanup(philos, data->nb_of_philosophers, data);
		pthread_mutex_lock(&data->print_mutex);
		printf("Error : Thread creation failure for monitor\n");
		pthread_mutex_unlock(&data->print_mutex);
		return (NULL);
	}
	return (monitor);
}
