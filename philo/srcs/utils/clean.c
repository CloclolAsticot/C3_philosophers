/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:01:28 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/04 16:33:12 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include <stdlib.h>

/**
 * @brief Cleans up and destroys a dynamically allocated array of forks.
 * 
 * @param forks_array Pointer to the array of t_fork structures to be cleaned.
 * @param array_size Number of elements in the forks array.
 */
void	clean_forks_array(t_fork *forks_array, unsigned int array_size)
{
	unsigned int	i;

	i = 0;
	while (i < array_size)
	{
		pthread_mutex_destroy(&forks_array[i].fork_mutex);
		i++;
	}
	free(forks_array);
}

/**
 * @brief Cleans up and destroys all mutexes in the philosophers array and frees
 * memory.
 * 
 * @param philos_array Pointer to the array of philosopher structures to be 
 * cleaned up.
 * @param array_size Number of philosophers in the array.
 */
void	clean_philos_array(t_philo *philos_array, unsigned int array_size)
{
	unsigned int	i;

	i = 0;
	while (i < array_size)
	{
		pthread_mutex_destroy(&philos_array[i].last_meal_mutex);
		pthread_mutex_destroy(&philos_array[i].remaining_meals_mutex);
		i++;
	}
	free(philos_array);
}

/**
 * @brief Cleans up all allocated resources and destroys mutexes for the 
 * philosopher simulation.
 *
 * @param philos Pointer to the array of philosopher structures (can be NULL).
 * @param data Pointer to the main data structure.
 */
void	clean_all(t_philo *philos, t_data *data)
{
	clean_forks_array(data->forks, data->nb_of_philosophers);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_sim_mutex);
	if (philos != NULL)
		clean_philos_array(philos, data->nb_of_philosophers);
}
