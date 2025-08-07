/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:19:13 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/04 16:31:44 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>

/**
 * @brief Safely checks if the simulation should stop.
 *
 * @param stop_sim Pointer to the boolean flag indicating simulation stop
 * status.
 * @param stop_sim_mutex Pointer to the mutex protecting the stop_sim flag.
 * @return true if the simulation should stop, false otherwise.
 */
static bool	stop_sim_check(bool *stop_sim, pthread_mutex_t *stop_sim_mutex)
{
	pthread_mutex_lock(stop_sim_mutex);
	if (*stop_sim == true)
	{
		pthread_mutex_unlock(stop_sim_mutex);
		return (true);
	}
	pthread_mutex_unlock(stop_sim_mutex);
	return (false);
}

/**
 * @brief Attempts to grab a fork for a philosopher.
 *
 * @param fork_status Pointer to the boolean status of the fork.
 * @param fork_mutex Pointer to the mutex protecting the fork status.
 * @param data Pointer to the shared simulation data structure.
 * @param philo Pointer to the philosopher structure attempting to grab the
 * fork.
 *
 * @return true if the fork was successfully grabbed, false if the simulation
 * was stopped.
 */
static bool	grab_fork(bool *fork_status, pthread_mutex_t *fork_mutex,
		t_data *data, t_philo *philo)
{
	bool	grab_succeeded;

	grab_succeeded = false;
	while (stop_sim_check(&data->stop_sim, &data->stop_sim_mutex) == false
		&& grab_succeeded == false)
	{
		pthread_mutex_lock(fork_mutex);
		if (*fork_status == false)
		{
			*fork_status = true;
			if (protected_print_log(data->sim_start_time, philo->id, FORK_MSG,
					data) == false)
			{
				pthread_mutex_unlock(fork_mutex);
				return (false);
			}
			grab_succeeded = true;
		}
		pthread_mutex_unlock(fork_mutex);
		if (grab_succeeded == false)
			usleep(100);
	}
	return (grab_succeeded);
}

/**
 * @brief Attempts to grab both left and right forks for a philosopher.
 *
 * @param left_fork Pointer to the left fork structure.
 * @param right_fork Pointer to the right fork structure .
 * @param philo Pointer to the philosopher structure.
 * @param data Pointer to the shared data structure.
 *
 * @return true if both forks were successfully grabbed, false otherwise.
 */
bool	grab_both_forks(t_fork *left_fork, t_fork *right_fork, t_philo *philo,
		t_data *data)
{
	if (grab_fork(&left_fork->fork_status, &left_fork->fork_mutex, data,
			philo) == true)
		if (grab_fork(&right_fork->fork_status, &right_fork->fork_mutex, data,
				philo) == true)
			return (true);
	return (false);
}

/**
 * @brief Releases both left and right forks by setting their status to false.
 *
 * @param left_fork_status Pointer to the boolean status of the left fork.
 * @param left_fork_mutex Pointer to the mutex protecting the left fork.
 * @param right_fork_status Pointer to the boolean status of the right fork.
 * @param right_fork_mutex Pointer to the mutex protecting the right fork.
 */
void	put_forks_down(bool *left_fork_status, pthread_mutex_t *left_fork_mutex,
		bool *right_fork_status, pthread_mutex_t *right_fork_mutex)
{
	protected_bool_update(left_fork_status, false, left_fork_mutex);
	protected_bool_update(right_fork_status, false, right_fork_mutex);
}
