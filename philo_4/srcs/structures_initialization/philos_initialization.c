/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_initialization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:37:33 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/24 16:45:05 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void *initialize_meal_parameters(t_philo *philos, unsigned int i, t_data * data)
{
    if (pthread_mutex_init(&philos[i].last_meal_mutex, NULL) != 0)
	{
		printf("Error : mutex initialization fail on last_meal_mutex\n");
		clean_forks_array(data->forks, data->nb_of_philosophers);
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->stop_sim_mutex);
		clean_philos_array(philos, i);
		return (NULL);
	}
	philos[i].last_meal = data->sim_start_time;
    if (pthread_mutex_init(&philos[i].remaining_meals_mutex, NULL) != 0)
	{
		printf("Error : mutex initialization fail on remaining_meals_mutex\n");
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
 * @param data Pointer to the datauration structure containing simulation 
 * 				 parameters.
 */
void	*initialize_philos(t_data *data)
{
	t_philo *philos;
	unsigned int	i;

	philos = malloc(data->nb_of_philosophers * sizeof(t_philo));
	if (philos == NULL)
	{
		printf("Error : malloc failed for philos[]\n");
		clean_all(NULL, data);
		return (NULL);
	}
	i = 0;
	while (i < data->nb_of_philosophers)
	{
		if (initialize_meal_parameters(philos, i, data) == NULL)
			return (NULL);
		philos[i].id = i + 1;	// init ID
		philos[i].left_fork = &(data->forks[i]);	// init left fork
		philos[i].right_fork = &(data->forks[(i + 1)	// init right fork
				% data->nb_of_philosophers]);
		philos[i].last_meal = data->sim_start_time;	// init last meal time
		philos[i].data = data;
		i++;
	}
	return (philos);
}

