/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:32:59 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/04 16:32:18 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "threads_handling.h"
#include "utils.h"

/**
 * @brief Handles cleanup when thread creation fails during philosopher 
 * simulation setup.
 * 
 * @param philos Pointer to the array of philosopher structures.
 * @param nb_of_philo_threads Number of philosopher threads that were 
 * successfully created.
 * @param data Pointer to the shared data structure.
 */
static void	thread_creation_failure_cleanup(t_philo *philos,
		unsigned int nb_of_philo_threads, t_data *data)
{
	protected_bool_update(&data->stop_sim, true, &data->stop_sim_mutex);
	terminate_philo_threads(philos, nb_of_philo_threads, data);
	clean_all(philos, data);
}

/**
 * @brief Creates and starts philosopher threads with alternating routines.
 * 
 * @param philos Pointer to array of philosopher structures.
 * @param nb_of_philos Total number of philosophers to create threads for.
 * @param data Pointer to shared data structure.
 * 
 * @return Pointer to the philos array on success, NULL on thread creation
 * failure.
 */
void	*create_philo_threads(t_philo *philos, unsigned int nb_of_philos,
		t_data *data)
{
	unsigned int	i;
	int				thread_creation_return;

	i = 0;
	while (i < nb_of_philos)
	{
		if (philos[i].id == 0)
			break ;
		if (philos[i].id % 2 == 0)
			thread_creation_return = pthread_create(&philos[i].thread_id, NULL,
					&philo_routine_even, &philos[i]);
		else
			thread_creation_return = pthread_create(&philos[i].thread_id, NULL,
					&philo_routine_odd, &philos[i]);
		if (thread_creation_return != 0)
		{
			thread_creation_failure_cleanup(philos, i, data);
			protected_print_error(THREAD_CREATION_FAIL, &data->print_mutex);
			return (NULL);
		}
		i++;
	}
	return (philos);
}

/**
 * @brief Creates and starts a monitor thread for the philosopher simulation.
 * 
 * @param monitor Pointer to pthread_t where the created thread ID will be 
 * stored.
 * @param philos Pointer to the array of philosopher structures that will be
 *               passed to the monitor routine.
 * @param data Pointer to the main data structure.
 * 
 * @return Returns the monitor pthread_t pointer on success, NULL on failure
 */
void	*create_monitor_thread(pthread_t *monitor, t_philo *philos,
		t_data *data)
{
	if (pthread_create(monitor, NULL, &monitor_routine, philos) != 0)
	{
		thread_creation_failure_cleanup(philos, data->nb_of_philosophers, data);
		protected_print_error(THREAD_CREATION_FAIL, &data->print_mutex);
		return (NULL);
	}
	return (monitor);
}
