/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:43:25 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/24 17:04:45 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include <pthread.h>
#include <unistd.h>

static bool stop_sim_check(t_data *data)
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

static bool grab_fork(t_fork *fork, t_data *data)
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
		usleep(100);
	}
    return (grab_succeeded);
}

static bool	grab_both_forks(t_philo *philo, t_fork *left_fork,
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

void	*philo_routine(void *arg)
{
	t_data			*data;
    t_philo         *philo;
    
	philo = (t_philo *)arg;
    data = philo->data;
    // THINK
    if (protected_print_log(get_time_diff_ms(data->sim_start_time), philo->id, THINK_MSG, data) == false)
        return (NULL);
    if (philo->id % 2 == 0)
        usleep(100);
    while (1)
    {
        // EAT
        if (grab_both_forks(philo, philo->left_fork, philo->right_fork, data) == false)
            return (NULL);
        if (protected_print_log(get_time_diff_ms(data->sim_start_time), philo->id, FORK_MSG, data) == false)
            return (NULL);
        if (protected_print_log(get_time_diff_ms(data->sim_start_time), philo->id, FORK_MSG, data) == false)
            return (NULL);
        pthread_mutex_lock(&philo->last_meal_mutex);
        philo->last_meal = get_current_time_ms();
        pthread_mutex_lock(&philo->remaining_meals_mutex);
        if (philo->remaining_meals > 0)
            philo->remaining_meals--;
        pthread_mutex_unlock(&philo->remaining_meals_mutex);
        pthread_mutex_unlock(&philo->last_meal_mutex);
        if (protected_print_log(get_time_diff_ms(data->sim_start_time), philo->id, EAT_MSG, data) == false)
            return (NULL);
        usleep(data->time_to_eat * 1000);
        // TAKE DOWN FORKS
        pthread_mutex_lock(&philo->left_fork->fork_mutex);
        philo->left_fork->fork_status = false;
        pthread_mutex_unlock(&philo->left_fork->fork_mutex);
        pthread_mutex_lock(&philo->right_fork->fork_mutex);
        philo->right_fork->fork_status = false;
        pthread_mutex_unlock(&philo->right_fork->fork_mutex);
        // SLEEP
        if (protected_print_log(get_time_diff_ms(data->sim_start_time), philo->id, SLEEP_MSG, data) == false)
            return (NULL);
        usleep(data->time_to_sleep * 1000);
        // THINK
        if (protected_print_log(get_time_diff_ms(data->sim_start_time), philo->id, THINK_MSG, data) == false)
            return (NULL);
    }
}
