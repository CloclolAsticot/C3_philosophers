/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:50:19 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/16 17:02:54 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures_initialization.h"
#include "utils.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void clean_all(t_philo *philos, t_config * config)
{
	long i;
	
	i = 0;
	while (i < config->number_of_philosophers)
	{
		pthread_mutex_destroy(&config->fork[i]);
		i++;
	}
	free(config->fork);
	pthread_mutex_destroy(&config->print_mutex);
	if (philos != NULL)
		free(philos);
}

void create_philo_threads(t_philo *philos, t_config *config)
{
	unsigned int i;
	unsigned int nb_of_philos;

	nb_of_philos = config->number_of_philosophers;
	i = 0;
	while (i < nb_of_philos)
	{
		pthread_create(&philos[i].thread_id, NULL, &philo_routine, &philos[i]);
		i++;
	}
}

int	main(int ac, char *av[])
{
	t_config	config;
	t_philo		*philos;
	pthread_t	monitor;

	if (ac < 5 || ac > 6)
	{
		printf("Error : Wrong number of arguments\n");
		return (EXIT_FAILURE);
	}
	if (initialize_config(av, &config) == NULL)
		return (EXIT_FAILURE);
	philos = malloc((config.number_of_philosophers + 1) * sizeof(t_philo));
	if (philos == NULL)
	{
		printf("Error : malloc fail\n");
		clean_all(NULL, &config);
		return (EXIT_FAILURE);
	}
	memset(philos, 0, (config.number_of_philosophers + 1) * sizeof(t_philo));
	initialize_philos(philos, &config);

	create_philo_threads(philos, &config);
	pthread_create(&monitor, NULL, &monitor_routine, philos);
	pthread_join(monitor, NULL);
	terminate_threads(philos, &config);
	clean_all(philos, &config);
	return (EXIT_SUCCESS);
}
