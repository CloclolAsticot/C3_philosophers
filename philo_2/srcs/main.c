/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:50:19 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/17 16:35:39 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "threads_handling.h"
#include "structures_initialization.h"
#include "utils.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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
	philos = (t_philo *)initialize_philos(&config);
	if (philos == NULL)
		return (EXIT_FAILURE);
	if (create_threads(philos, &monitor, &config) == NULL)
		return (EXIT_FAILURE);
	pthread_join(monitor, NULL);
	terminate_philos_threads(philos, config.number_of_philosophers);
	clean_all(philos, &config);
	return (EXIT_SUCCESS);
}
