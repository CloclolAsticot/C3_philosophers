/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:19:13 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/03 18:25:17 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "threads_handling.h"
#include "utils.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <unistd.h>

bool	stop_sim_check(bool *stop_sim, pthread_mutex_t *stop_sim_mutex)
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

bool	grab_fork(bool *fork_status, pthread_mutex_t *fork_mutex, t_data *data,
		t_philo *philo)
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