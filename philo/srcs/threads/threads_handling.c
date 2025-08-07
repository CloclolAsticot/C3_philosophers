/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:32:59 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/07 11:48:12 by csavreux         ###   ########lyon.fr   */
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
 * @brief Terminates and waits for all philosopher threads to complete.
 * 
 * @param philos Pointer to array of philosopher structures containing
 * thread IDs.
 * @param nb_of_threads Number of philosopher threads to join.
 * @param data Pointer to shared data structure.
 */
void	terminate_philo_threads(t_philo *philos, unsigned int nb_of_threads,
		t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < nb_of_threads)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
			protected_print_error(THREAD_JOIN_FAIL, &data->print_mutex);
		i++;
	}
}
