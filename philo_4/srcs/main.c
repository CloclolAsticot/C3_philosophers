/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:50:19 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/24 16:44:16 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures_initialization.h"
#include "utils.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "threads_handling.h"

int	main(int ac, char *av[])
{
	t_data	data;
	t_philo		*philos;
	pthread_t	monitor;

	if (ac < 5 || ac > 6)
	{
		printf("Error : Wrong number of arguments\n");
		return (EXIT_FAILURE);
	}
	if (initialize_data(av, &data) == NULL)
		return (EXIT_FAILURE);
	philos = initialize_philos(&data);
	if (philos == NULL)
		return (EXIT_FAILURE);
	create_philo_threads(philos, &data);
	pthread_create(&monitor, NULL, &monitor_routine, philos);
	pthread_join(monitor, NULL);
	terminate_threads(philos, &data);
	clean_all(philos, &data);
	return (EXIT_SUCCESS);
}
