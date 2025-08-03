/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_initialization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:50:42 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/24 15:07:13 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "structures_initialization.h"
#include "utils.h"
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include "utils.h"

/**
 * @brief Initializes the datauration structure with user input parameters.
 * 
 * @param user_input Array of strings containing the simulation parameters.
 * @param data Pointer to the datauration structure to be initialized.
 * 
 * @return Pointer to the initialized data structure on success, NULL on
 * 		   failure.
 */
static void	*initialize_user_input(char *user_input[], t_data *data)
{
	long	nb;
	int		i;

	i = 1;
	while (i <= 4 || (i == 5 && user_input[5] != NULL))
	{
		nb = check_and_convert_user_input(user_input[i]);
		if (nb == WRONG_FORMAT)
			return (NULL);
		if (i == 1)
			data->nb_of_philosophers = nb;
		else if (i == 2)
			data->time_to_die = nb;
		else if (i == 3)
			data->time_to_eat = nb;
		else if (i == 4)
			data->time_to_sleep = nb;
		else if (i == 5)
			data->nb_of_required_meals = nb;
		i++;
	}
	if (i == 5 && user_input[5] == NULL)
		data->nb_of_required_meals = NO_ARG;
	return (data);
}


static void	*initialize_forks_array(unsigned int nb_of_philosophers)
{
	t_fork *forks;
	unsigned int i;
	
	forks = malloc(nb_of_philosophers * sizeof(t_fork));
	if (forks == NULL)
	{
		printf("Error : malloc failed for forks[] initialization\n");
		return (NULL);
	}
	i = 0;
	while (i < nb_of_philosophers)
	{
		if (pthread_mutex_init(&forks[i].fork_mutex, NULL) != 0)	// init mutexes + check for failure
		{
			printf("Error : mutex initialization failed for forks[%u].fork_mutex\n", i);
			clean_forks_array(forks, i);
			return (NULL);
		}
		forks[i].fork_status = false;
		i++;
	}
	return (forks);
}

static void *initialize_util_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0) // init print mutex
	{
		printf("Error : mutex initialization fail on print_mutex\n");
		clean_forks_array(data->forks, data->nb_of_philosophers);
		return (NULL);
	}
	if (pthread_mutex_init(&data->stop_sim_mutex, NULL) != 0) // init print mutex
	{
		printf("Error : mutex initialization fail on stop_sim_mutex\n");
		clean_forks_array(data->forks, data->nb_of_philosophers);
		pthread_mutex_destroy(&data->print_mutex);
		return (NULL);
	}
	return (data);
}

/**
 * @brief Initializes the datauration structure for the philosophers 
 * simulation.
 * 
 * @param user_input Array of command-line arguments containing simulation
 * 					 parameters.
 * @param data Pointer to the datauration structure to be initialized.
 * 
 * @return Pointer to the initialized data structure on success, NULL on 
 * 		   failure.
 */
void	*initialize_data(char *user_input[], t_data *data)
{
	if (initialize_user_input(user_input, data) == NULL || data->nb_of_philosophers == 0) // init user input values
	{
		printf("Error : Invalid argument (arguments must be unsigned integers - and nb_of_philosophers must be > 0)\n");
		return (NULL);
	}
	data->forks = initialize_forks_array(data->nb_of_philosophers);
	if (data->forks == NULL) // init forks[]
		return (NULL);
	if (initialize_util_mutexes(data) == NULL) // init print_mutex and stop_sim_mutex
		return (NULL);
	data->stop_sim = false;            // init has_a_philo_died
	// data->sim_start_time = get_current_time_ms(); // init sim_start_time
	return (data);
}



