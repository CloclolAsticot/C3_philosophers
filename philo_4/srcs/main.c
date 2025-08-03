/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:50:19 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/03 15:51:49 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures_initialization.h"
#include "threads_handling.h"
#include "utils.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int ac, char *av[])
{
	t_data		data;
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
	data.sim_start_time = get_current_time_ms();
	if (create_philo_threads(philos, data.nb_of_philosophers, &data) == NULL)
		return (EXIT_FAILURE);
	if (create_monitor_thread(&monitor, philos, &data) == NULL)
		return (EXIT_FAILURE);
	terminate_all_threads(philos, data.nb_of_philosophers, &monitor, &data);
	clean_all(philos, &data);
	return (EXIT_SUCCESS);
}
