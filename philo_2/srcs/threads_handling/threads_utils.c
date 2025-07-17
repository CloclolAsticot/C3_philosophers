/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:39:52 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/17 15:16:01 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "threads_handling.h"
#include <stdio.h>

void *create_threads(t_philo *philos, pthread_t *monitor, t_config *config)
{
	unsigned int i;
	unsigned int nb_of_philos;

	nb_of_philos = config->number_of_philosophers;
	i = 0;
	while (i < nb_of_philos)
	{
		if (pthread_create(&philos[i].thread_id, NULL, &philo_routine, &philos[i]) != 0)
		{
			printf("Error : thread creation failed for philos[%u]\n", i);
			protected_bool_update(&config->has_a_philo_died, true, config->death_bool_mutex);
			terminate_philos_threads(philos, i);
			return (NULL);
		}
		i++;
	}
	if (pthread_create(monitor, NULL, &monitor_routine, philos) != 0)
	{
		printf("Error : thread creation failed for monitor\n");
		terminate_philos_threads(philos, config->number_of_philosophers);
		return (NULL);
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