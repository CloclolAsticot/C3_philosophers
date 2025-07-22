/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:39:52 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/22 16:13:02 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "threads_handling.h"
#include "utils.h"
#include <pthread.h>
#include <stdio.h>

void *create_threads(t_philo *philos, t_config *config)
{
	unsigned int i;
	unsigned int nb_of_philos;

	nb_of_philos = config->number_of_philosophers;
	i = 0;
	while (i < nb_of_philos)
	{
		if (pthread_create(&philos[i].thread_id, NULL, &philo_routine, &philos[i]) != 0)
		{
			pthread_mutex_lock(&config->print_mutex);
			printf("Error : thread creation failed for philos[%u]\n", i);
			pthread_mutex_unlock(&config->print_mutex);
			protected_bool_update(&config->stop_sim, true, config->stop_sim_mutex);
			terminate_philos_threads(philos, i);
			clean_all(NULL, config);
			return (NULL);
		}
		i++;
	}
	return (philos);
}

void	terminate_philos_threads(t_philo *philos, unsigned int nb_of_threads)
{
	unsigned int	i;

	i = 0;
	while (i < nb_of_threads)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
}