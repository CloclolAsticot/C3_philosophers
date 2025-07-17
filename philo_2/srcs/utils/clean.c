/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:01:28 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/17 16:35:39 by csavreux         ###   ########lyon.fr   */
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

void clean_all(t_philo *philos, t_config * config)
{
	clean_forks_array(config->forks, config->number_of_philosophers);	// clean fork_mutexes and forks[]
	pthread_mutex_destroy(&config->print_mutex);	// clean print_mutex
	pthread_mutex_destroy(&config->death_bool_mutex);	// clean death_bool_mutex
	if (philos != NULL)
		free(philos);	// clean philos[]
}
