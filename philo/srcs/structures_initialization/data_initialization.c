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

#include "structures_initialization.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Initializes the data structure with user input parameters.
 *
 * @param user_input Array of strings containing the simulation parameters.
 * @param data Pointer to the data structure to be initialized.
 *
 * @return Pointer to the initialized data structure on success, NULL on
 * 			failure.
 */
static void	*initialize_user_input(char *user_input[], t_data *data)
{
	long	nb;
	int		i;

	i = 1;
	while (i <= 4 || (i == 5 && user_input[5] != NULL))
	{
		nb = check_and_convert_user_input(user_input[i]);
		if (nb == WRONG_FORMAT_NB)
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

/**
 * @brief Initializes an array of forks.
 *
 * @param nb_of_philosophers The number of philosophers (and therefore forks)
 * to create.
 * @return Pointer to the initialized forks array on success, NULL on failure.
 */
static void	*initialize_forks_array(unsigned int nb_of_philosophers)
{
	t_fork			*forks;
	unsigned int	i;

	forks = malloc(nb_of_philosophers * sizeof(t_fork));
	if (forks == NULL)
	{
		print_error(MALLOC_FAIL);
		return (NULL);
	}
	i = 0;
	while (i < nb_of_philosophers)
	{
		if (pthread_mutex_init(&forks[i].fork_mutex, NULL) != 0)
		{
			print_error(MUTEX_FAIL);
			clean_forks_array(forks, i);
			return (NULL);
		}
		forks[i].fork_status = false;
		i++;
	}
	return (forks);
}

/**
 * @brief Initializes utility mutexes for the data structure.
 * 
 * @param data Pointer to the main data structure.
 * @return Returns the data pointer on success, NULL on failure.
 */
static void	*initialize_util_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		print_error(MUTEX_FAIL);
		clean_forks_array(data->forks, data->nb_of_philosophers);
		return (NULL);
	}
	if (pthread_mutex_init(&data->stop_sim_mutex, NULL) != 0)
	{
		printf(MUTEX_FAIL);
		clean_forks_array(data->forks, data->nb_of_philosophers);
		pthread_mutex_destroy(&data->print_mutex);
		return (NULL);
	}
	return (data);
}

/**
 * @brief Initializes the data structure for the philosophers
 * simulation.
 *
 * @param user_input Array of command-line arguments containing simulation
 * 						parameters.
 * @param data Pointer to the data structure to be initialized.
 *
 * @return Pointer to the initialized data structure on success, NULL on
 * 			failure.
 */
void	*initialize_data(char *user_input[], t_data *data)
{
	if (initialize_user_input(user_input, data) == NULL)
	{
		printf(ARG_NOT_UINT);
		return (NULL);
	}
	if (data->nb_of_philosophers == 0)
	{
		printf(ZERO_PHILO);
		return (NULL);
	}
	if (data->nb_of_required_meals == 0)
	{
		printf(ZERO_MEAL);
		return (NULL);
	}
	data->forks = initialize_forks_array(data->nb_of_philosophers);
	if (data->forks == NULL)
		return (NULL);
	if (initialize_util_mutexes(data) == NULL)
		return (NULL);
	data->stop_sim = false;
	data->sim_start_time = get_current_time_ms();
	return (data);
}
