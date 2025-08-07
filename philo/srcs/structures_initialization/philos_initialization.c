/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_initialization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:37:33 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/04 16:30:24 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

/**
 * @brief Initializes meal-related parameters for a philosopher.
 * 
 * @param philos Pointer to the array of philosopher structures.
 * @param i Index of the philosopher to initialize.
 * @param data Pointer to the shared data structure containing simulation 
 * parameters.
 * 
 * @return Pointer to the initialized philosopher on success, NULL on failure.
 */
static void	*initialize_meal_parameters(t_philo *philos, unsigned int i,
		t_data *data)
{
	if (pthread_mutex_init(&philos[i].last_meal_mutex, NULL) != 0)
	{
		print_error(MUTEX_FAIL);
		clean_forks_array(data->forks, data->nb_of_philosophers);
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->stop_sim_mutex);
		clean_philos_array(philos, i);
		return (NULL);
	}
	philos[i].last_meal = data->sim_start_time;
	if (pthread_mutex_init(&philos[i].remaining_meals_mutex, NULL) != 0)
	{
		print_error(MUTEX_FAIL);
		clean_forks_array(data->forks, data->nb_of_philosophers);
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->stop_sim_mutex);
		pthread_mutex_destroy(&philos[i].last_meal_mutex);
		clean_philos_array(philos, i);
		return (NULL);
	}
	if (data->nb_of_required_meals != NO_ARG)
		philos[i].remaining_meals = data->nb_of_required_meals;
	else
		philos[i].remaining_meals = -1;
	return (&philos[i]);
}

/**
 * @brief Initializes an array of philosopher structures with their initial
 * values.
 *
 * @param philos Pointer to the array of philosopher structures to initialize.
 * @param data Pointer to the data structure containing simulation
 * 					parameters.
 *
 * @return Pointer to the initialized philos array on success, NULL on failure.
 */
void	*initialize_philos(t_data *data)
{
	t_philo			*philos;
	unsigned int	i;

	philos = malloc((data->nb_of_philosophers + 1) * sizeof(t_philo));
	if (philos == NULL)
	{
		print_error(MALLOC_FAIL);
		clean_all(NULL, data);
		return (NULL);
	}
	i = 0;
	while (i < data->nb_of_philosophers)
	{
		if (initialize_meal_parameters(philos, i, data) == NULL)
			return (NULL);
		philos[i].id = i + 1;
		philos[i].left_fork = &(data->forks[i]);
		philos[i].right_fork = &(data->forks[(i + 1)
				% data->nb_of_philosophers]);
		philos[i].last_meal = data->sim_start_time;
		philos[i].data = data;
		i++;
	}
	philos[i].id = 0;
	return (philos);
}
