/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:02:30 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/24 17:45:37 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

static bool death_check_and_update(t_data *data, t_philo *philo)
{
    pthread_mutex_lock(&philo->last_meal_mutex);
    if (get_time_diff_ms(philo->last_meal) >= data->time_to_die)
    {
        pthread_mutex_lock(&data->stop_sim_mutex);
        data->stop_sim = true;
        print_log(get_time_diff_ms(philo->last_meal), philo->id, DEATH_MSG, data);
        pthread_mutex_unlock(&data->stop_sim_mutex);
        pthread_mutex_unlock(&philo->last_meal_mutex);
        return (true);
    }
    pthread_mutex_unlock(&philo->last_meal_mutex);
    return (false);
}

static void satiaty_counter_update(unsigned int *satiated_philos_counter, t_philo *philo)
{
    pthread_mutex_lock(&philo->remaining_meals_mutex);
    if (philo->remaining_meals == 0)
        (*satiated_philos_counter)++;
    pthread_mutex_unlock(&philo->remaining_meals_mutex);
}

void	*monitor_routine(void *arg)
{
	t_data			*data;
    t_philo         *philos;
    unsigned int satiated_philos_counter;
    unsigned int i;
    
    philos = (t_philo *)arg;
    data = philos[0].data;
    satiated_philos_counter = 0;
	while (satiated_philos_counter < data->nb_of_philosophers)
	{
        satiated_philos_counter = 0;
        i = 0;
		while (i < data->nb_of_philosophers)
        {
            if (death_check_and_update(data, &philos[i]) == true)
                return (NULL);
            satiaty_counter_update(&satiated_philos_counter, &philos[i]);
            i++;
            usleep(100);
        }
	}
    pthread_mutex_lock(&data->stop_sim_mutex);
    data->stop_sim = true;
    pthread_mutex_unlock(&data->stop_sim_mutex);
	return (NULL);
}
