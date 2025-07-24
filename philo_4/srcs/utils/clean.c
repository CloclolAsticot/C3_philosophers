/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:01:28 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/24 17:40:01 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include <pthread.h>
#include <stdlib.h>

void clean_forks_array(t_fork *forks_array, unsigned int array_size)
{
	unsigned int i;

	i = 0;
	while (i < array_size)
	{
		pthread_mutex_destroy(&forks_array[i].fork_mutex);
		i++;
	}
	free(forks_array);
}

void clean_philos_array(t_philo *philos_array, unsigned int array_size)
{
    unsigned int i;

    i = 0;
    while (i < array_size)
    {
        pthread_mutex_destroy(&philos_array[i].last_meal_mutex);
        pthread_mutex_destroy(&philos_array[i].remaining_meals_mutex);
        i++;
    }
    free(philos_array);
}

void clean_all(t_philo *philos, t_data * data)
{
	clean_forks_array(data->forks, data->nb_of_philosophers);	// clean fork_mutexes and forks[]
	pthread_mutex_destroy(&data->print_mutex);	// clean print_mutex
	pthread_mutex_destroy(&data->stop_sim_mutex);	// clean death_bool_mutex
	if (philos != NULL)
		clean_philos_array(philos, data->nb_of_philosophers);
}