/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:43:25 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/24 17:40:16 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include <pthread.h>
#include <unistd.h>
#include "threads_handling.h"

static void *think(t_philo *philo, t_data *data)
{
    if (protected_print_log(get_time_diff_ms(data->sim_start_time), philo->id, THINK_MSG, data) == false)
        return (NULL);
    return (philo);
}

static void *eat(t_philo *philo, t_data *data)
{
    if (grab_both_forks(philo, philo->left_fork, philo->right_fork, data) == false)
        return (NULL);
    pthread_mutex_lock(&philo->last_meal_mutex);
    philo->last_meal = get_current_time_ms();
    pthread_mutex_unlock(&philo->last_meal_mutex);
    if (protected_print_log(get_time_diff_ms(data->sim_start_time), philo->id, FORK_MSG, data) == false)
        return (NULL);
    if (protected_print_log(get_time_diff_ms(data->sim_start_time), philo->id, FORK_MSG, data) == false)
        return (NULL);
    pthread_mutex_lock(&philo->remaining_meals_mutex);
    if (philo->remaining_meals > 0)
        philo->remaining_meals--;
    pthread_mutex_unlock(&philo->remaining_meals_mutex);
    if (protected_print_log(get_time_diff_ms(data->sim_start_time), philo->id, EAT_MSG, data) == false)
        return (NULL);
    usleep(data->time_to_eat * 1000);
    return (philo);
}

static void put_forks_down(t_philo *philo)
{
    pthread_mutex_lock(&philo->left_fork->fork_mutex);
    philo->left_fork->fork_status = false;
    pthread_mutex_unlock(&philo->left_fork->fork_mutex);
    pthread_mutex_lock(&philo->right_fork->fork_mutex);
    philo->right_fork->fork_status = false;
    pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}

static void *p_sleep(t_philo *philo, t_data *data)
{
    if (protected_print_log(get_time_diff_ms(data->sim_start_time), philo->id, SLEEP_MSG, data) == false)
        return (NULL);
    usleep(data->time_to_sleep * 1000);
    return (philo);
}

void	*philo_routine_even(void *arg)
{
	t_data			*data;
    t_philo         *philo;
    
	philo = (t_philo *)arg;
    data = philo->data;
    while (1)
    {
        // THINK
        if (think(philo, data) == NULL)
            return (NULL);
        // EAT
        if (eat(philo, data) == NULL)
            return (NULL);
        // TAKE DOWN FORKS
        put_forks_down(philo);
        // SLEEP
        if (p_sleep(philo, data) == NULL)
            return (NULL);
    }
    return (NULL);
}

void	*philo_routine_odd(void *arg)
{
	t_data			*data;
    t_philo         *philo;
    
	philo = (t_philo *)arg;
    data = philo->data;
    while (1)
    {
        // SLEEP
        if (p_sleep(philo, data) == NULL)
            return (NULL);
        // THINK
        if (think(philo, data) == NULL)
            return (NULL);
        // EAT
        if (eat(philo, data) == NULL)
            return (NULL);
        // TAKE DOWN FORKS
        put_forks_down(philo);
    }
    return (NULL);
}
