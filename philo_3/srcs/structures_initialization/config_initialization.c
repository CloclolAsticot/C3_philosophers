/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_initialization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:50:42 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/22 16:46:59 by csavreux         ###   ########lyon.fr   */
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
static void	*initialize_forks_array(unsigned int nb_of_philosophers)
{
	t_fork *forks;
	unsigned int i;
	
	forks = malloc((nb_of_philosophers + 1)	// malloc the forks array
			* sizeof(t_fork));
	if (forks == NULL)
	{
		printf("Error : malloc failed for forks[] initialization\n");
		return (NULL);
	}
	i = 0;
	while (i < nb_of_philosophers)
	{
		forks[i].is_fork_used = false;
		if (pthread_mutex_init(&forks[i].fork_mutex, NULL) != 0)	// init mutexes + check for failure
		{
			printf("Error : mutex initialization failed for forks[%u].fork_mutex\n", i);
			clean_forks_array(forks, i);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static void *initialize_util_mutexes(t_config *config)
{
	if (pthread_mutex_init(&config->print_mutex, NULL) != 0) // init print mutex
	{
		printf("Error : mutex initialization fail on print_mutex\n");
		clean_forks_array(config->forks, config->number_of_philosophers);
		return (NULL);
	}
	if (pthread_mutex_init(&config->stop_sim_mutex, NULL) != 0) // init print mutex
	{
		printf("Error : mutex initialization fail on stop_sim_mutex\n");
		clean_forks_array(config->forks, config->number_of_philosophers);
		pthread_mutex_destroy(&config->print_mutex);
		return (NULL);
	}
	if (pthread_mutex_init(&config->satiated_philos_counter_mutex, NULL) != 0) // init print mutex
	{
		printf("Error : mutex initialization fail on satiated_philos_counter_mutex\n");
		clean_forks_array(config->forks, config->number_of_philosophers);
		pthread_mutex_destroy(&config->print_mutex);
		pthread_mutex_destroy(&config->stop_sim_mutex);
		return (NULL);
	}
	return (config);
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
	if (initialize_user_input(user_input, config) == NULL) // init user input values
	{
		printf("Error : Wrong argument format\n");
		return (NULL);
	}
	config->forks = initialize_forks_array(config->number_of_philosophers);
	if (config->forks == NULL) // init forks[]
		return (NULL);
	if (initialize_util_mutexes(config) == NULL) // init print_mutex and death_bool_mutex
		return (NULL);
	config->stop_sim = false;            // init has_a_philo_died
	config->sim_start_time = get_current_time_ms(); // init sim_start_time
	config->satiated_philos_counter = 0;
	return (config);
}

