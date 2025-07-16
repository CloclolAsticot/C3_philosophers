/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_initialization.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:50:42 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/16 17:26:09 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures_initialization.h"
#include "utils.h"
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

/**
 * @brief Initializes the configuration structure with user input parameters.
 * 
 * @param user_input Array of strings containing the simulation parameters.
 * @param config Pointer to the configuration structure to be initialized.
 * 
 * @return Pointer to the initialized config structure on success, NULL on
 * 		   failure.
 */
static void	*initialize_user_input(char *user_input[], t_config *config)
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
			config->number_of_philosophers = nb;
		else if (i == 2)
			config->time_to_die = nb;
		else if (i == 3)
			config->time_to_eat = nb;
		else if (i == 4)
			config->time_to_sleep = nb;
		else if (i == 5)
			config->number_of_times_each_philosopher_must_eat = nb;
		i++;
	}
	if (i == 5 && user_input[5] == NULL)
		config->number_of_times_each_philosopher_must_eat = NO_ARG;
	return (config);
}

/**
 * @brief Initializes an array of fork mutexes for the philosophers simulation.
 * 
 * @param config Pointer to the configuration structure.
 * 
 * @return Pointer to the initialized fork array on success, NULL on failure.
 */
static void	*initialize_forks(t_config *config)
{
	long	i;

	config->fork = malloc((config->number_of_philosophers + 1)	// malloc the fork array
			* sizeof(pthread_mutex_t));
	if (config->fork == NULL)
	{
		printf("Error : malloc failed during fork[] initialization\n");
		return (NULL);
	}
	memset(config->fork, 0, (config->number_of_philosophers + 1)	// init the fork array
		* sizeof(pthread_mutex_t));
	i = 0;
	while (i < config->number_of_philosophers)
	{
		if (pthread_mutex_init(&config->fork[i], NULL) != 0)	// init mutexes
		{
			while (--i >= 0)
				pthread_mutex_destroy(&config->fork[i]);
			free(config->fork);
			printf("Error : mutex initialization fail on forks\n");
			return (NULL);
		}
		i++;
	}
	return (config->fork);
}

/**
 * @brief Initializes the configuration structure for the philosophers 
 * simulation.
 * 
 * @param user_input Array of command-line arguments containing simulation
 * 					 parameters.
 * @param config Pointer to the configuration structure to be initialized.
 * 
 * @return Pointer to the initialized config structure on success, NULL on 
 * 		   failure.
 */
void	*initialize_config(char *user_input[], t_config *config)
{
	long	i;

	if (initialize_user_input(user_input, config) == NULL)
		// init user input values
	{
		printf("Error : Wrong argument format\n");
		return (NULL);
	}
	if (initialize_forks(config) == NULL) // init forks
		return (NULL);
	if (pthread_mutex_init(&config->print_mutex, NULL) != 0) // init print mutex
	{
		i = 0;
		while (i < config->number_of_philosophers)
		{
			pthread_mutex_destroy(&config->fork[i]);
			i++;
		}
		free(config->fork);
		printf("Error : mutex initialization fail on print_mutex\n");
		return (NULL);
	}
	if (pthread_mutex_init(&config->death_bool_mutex, NULL) != 0) // init print mutex
	{
		i = 0;
		while (i < config->number_of_philosophers)
		{
			pthread_mutex_destroy(&config->fork[i]);
			i++;
		}
		pthread_mutex_destroy(&config->print_mutex);
		free(config->fork);
		printf("Error : mutex initialization fail on print_mutex\n");
		return (NULL);
	}
	config->has_a_philo_died = false;            // init bool
	config->sim_start_time = get_current_time_ms(); // init sim_start_time
	return (config);
}

/**
 * @brief Initializes an array of philosopher structures with their initial 
 * values.
 * 
 * @param philos Pointer to the array of philosopher structures to initialize.
 * @param config Pointer to the configuration structure containing simulation 
 * 				 parameters.
 */
void	initialize_philos(t_philo *philos, t_config *config)
{
	long	i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		philos[i].id = i + 1;	// init ID
		philos[i].left_fork = &(config->fork[i]);	// init left fork
		philos[i].right_fork = &(config->fork[(i + 1)	// init right fork
				% config->number_of_philosophers]);
		philos[i].nb_of_meals = 0;	// init nb of meals
		philos[i].config = config;	// init config (so each philo has its informations)
		philos[i].last_meal_time = config->sim_start_time;	// init last meal time
		i++;
	}
}
