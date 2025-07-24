/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:19:13 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/24 17:42:33 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "threads_handling.h"
#include <pthread.h>
#include <unistd.h>

bool stop_sim_check(t_data *data)
{
    pthread_mutex_lock(&data->stop_sim_mutex);
    if (data->stop_sim == true)
    {
        pthread_mutex_unlock(&data->stop_sim_mutex);
        return (true);
    }
    pthread_mutex_unlock(&data->stop_sim_mutex);
    return (false);
}

bool grab_fork(t_fork *fork, t_data *data)
{
    bool grab_succeeded;

    grab_succeeded = false;
    while (stop_sim_check(data) == false && grab_succeeded == false)
	{
		pthread_mutex_lock(&fork->fork_mutex);
		if (fork->fork_status == false)
		{
			fork->fork_status = true;
			grab_succeeded = true;
		}
		pthread_mutex_unlock(&fork->fork_mutex);
		usleep(50);
	}
    return (grab_succeeded);
}

bool	grab_both_forks(t_philo *philo, t_fork *left_fork,
		t_fork *right_fork, t_data *data)
{
	if (philo->id % 2 == 0)
    {
        if (grab_fork(left_fork, data) == true && grab_fork(right_fork, data) == true)
            return (true);
    }
	else if (philo->id % 2 != 0)
    {
        if (grab_fork(right_fork, data) == true && grab_fork(left_fork, data) == true)
            return (true);
    }
    return (false);
}