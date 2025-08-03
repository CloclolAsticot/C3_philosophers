/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:43:25 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/03 19:30:39 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "threads_handling.h"
#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static void	*think(long sim_start_time, unsigned int philo_id, t_data *data)
{
	if (protected_print_log(sim_start_time, philo_id, THINK_MSG, data) == false)
		return (NULL);
	return (data);
}

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

static void	put_forks_down(bool *left_fork_status,
		pthread_mutex_t *left_fork_mutex, bool *right_fork_status,
		pthread_mutex_t *right_fork_mutex)
{
	protected_bool_update(left_fork_status, false, left_fork_mutex);
	protected_bool_update(right_fork_status, false, right_fork_mutex);
}

static void	*p_sleep(t_philo *philo, t_data *data)
{
	if (protected_print_log(data->sim_start_time, philo->id, SLEEP_MSG,
			data) == false)
		return (NULL);
	usleep(data->time_to_sleep * 1000);
	return (philo);
}

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
		// THINK
		if (think(sim_start_time, philo->id, data) == NULL)
			return (NULL);
		// EAT
		if (eat(sim_start_time, philo, data) == NULL)
			return (NULL);
		// TAKE DOWN FORKS
		put_forks_down(&philo->left_fork->fork_status,
			&philo->left_fork->fork_mutex, &philo->right_fork->fork_status,
			&philo->right_fork->fork_mutex);
		// SLEEP
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

	// bool			*stop_sim;
	// pthread_mutex_t	*stop_sim_mutex;
	philo = (t_philo *)arg;
	data = philo->data;
	sim_start_time = data->sim_start_time;
	// stop_sim = &data->stop_sim;
	// stop_sim_mutex = &data->stop_sim_mutex;
	while (1)
	{
		// SLEEP
		if (p_sleep(philo, data) == NULL)
			return (NULL);
		// THINK
		if (think(sim_start_time, philo->id, data) == NULL)
			return (NULL);
		// EAT
		if (eat(sim_start_time, philo, data) == NULL)
			return (NULL);
		// TAKE DOWN FORKS
		put_forks_down(&philo->left_fork->fork_status,
			&philo->left_fork->fork_mutex, &philo->right_fork->fork_status,
			&philo->right_fork->fork_mutex);
	}
	return (NULL);
}
