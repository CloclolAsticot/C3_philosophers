/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:43:25 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/04 16:32:02 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "threads_handling.h"
#include "utils.h"
#include <unistd.h>

/**
 * @brief Simulates a philosopher thinking state.
 * 
 * @param sim_start_time The simulation start time used for calculating 
 * elapsed time.
 * @param philo_id The unique identifier of the philosopher.
 * @param data Pointer to the shared data structure.
 * 
 * @return Returns the data pointer on success, NULL if the simulation stopped.
 */
static void	*think(long sim_start_time, unsigned int philo_id, t_data *data)
{
	if (protected_print_log(sim_start_time, philo_id, THINK_MSG, data) == false)
		return (NULL);
	return (data);
}

/**
 * @brief Simulates a philosopher eating by acquiring forks and updating 
 * meal status.
 * 
 * @param sim_start_time The simulation start time in milliseconds.
 * @param philo Pointer to the philosopher structure.
 * @param data Pointer to shared simulation data.
 * 
 * @return void* Returns pointer to the philosopher on success, NULL if 
 * the simulation stopped.
 */
static void	*eat(long sim_start_time, t_philo *philo, t_data *data)
{
	if (grab_both_forks(philo->left_fork, philo->right_fork, philo,
			data) == false)
		return (NULL);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_current_time_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (protected_print_log(sim_start_time, philo->id, EAT_MSG, data) == false)
		return (NULL);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->remaining_meals_mutex);
	if (philo->remaining_meals > 0)
		philo->remaining_meals--;
	pthread_mutex_unlock(&philo->remaining_meals_mutex);
	return (philo);
}

/**
 * @brief Simulates a philosopher sleeping for a specified duration.
 * 
 * @param philo Pointer to the philosopher structure.
 * @param data Pointer to the shared data structure.
 * 
 * @return void* Returns the philosopher pointer on success, NULL if 
 * the simulation has stopped.
 */
static void	*p_sleep(t_philo *philo, t_data *data)
{
	if (protected_print_log(data->sim_start_time, philo->id, SLEEP_MSG,
			data) == false)
		return (NULL);
	usleep(data->time_to_sleep * 1000);
	return (philo);
}

/**
 * @brief Philosopher routine for odd-numbered philosophers
 * 
 * @param arg Pointer to the philosopher structure (t_philo) cast as void*.
 *
 * @return void* Returns NULL when the routine terminates.
 */
void	*philo_routine_odd(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	long	sim_start_time;

	philo = (t_philo *)arg;
	data = philo->data;
	sim_start_time = data->sim_start_time;
	while (1)
	{
		if (think(sim_start_time, philo->id, data) == NULL)
			return (NULL);
		if (eat(sim_start_time, philo, data) == NULL)
			return (NULL);
		put_forks_down(&philo->left_fork->fork_status,
			&philo->left_fork->fork_mutex, &philo->right_fork->fork_status,
			&philo->right_fork->fork_mutex);
		if (p_sleep(philo, data) == NULL)
			return (NULL);
	}
	return (NULL);
}

void	*philo_routine_even(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	long	sim_start_time;

	philo = (t_philo *)arg;
	data = philo->data;
	sim_start_time = data->sim_start_time;
	while (1)
	{
		if (p_sleep(philo, data) == NULL)
			return (NULL);
		if (think(sim_start_time, philo->id, data) == NULL)
			return (NULL);
		if (eat(sim_start_time, philo, data) == NULL)
			return (NULL);
		put_forks_down(&philo->left_fork->fork_status,
			&philo->left_fork->fork_mutex, &philo->right_fork->fork_status,
			&philo->right_fork->fork_mutex);
	}
	return (NULL);
}
