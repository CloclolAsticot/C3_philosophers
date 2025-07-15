/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:50:19 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/15 16:59:41 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures_initialization.h"
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


int	main(int ac, char *av[])
{
	t_config	config;
	t_philo		*philos;

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
	clean_all(philos, &config);
	return (EXIT_SUCCESS);
}
