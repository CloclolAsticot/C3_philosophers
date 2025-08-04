/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:50:19 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/04 15:50:21 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures_initialization.h"
#include "threads_handling.h"
#include "utils.h"
#include <stdlib.h>

int	main(int ac, char *av[])
{
	t_data		data;
	t_philo		*philos;
	pthread_t	monitor;

	if (ac < 5 || ac > 6)
	{
		print_error(WRONG_ARG_NB);
		return (EXIT_FAILURE);
	}
	if (initialize_data(av, &data) == NULL)
		return (EXIT_FAILURE);
	philos = initialize_philos(&data);
	if (philos == NULL)
		return (EXIT_FAILURE);
	if (create_philo_threads(philos, data.nb_of_philosophers, &data) == NULL)
		return (EXIT_FAILURE);
	if (create_monitor_thread(&monitor, philos, &data) == NULL)
		return (EXIT_FAILURE);
	terminate_all_threads(philos, data.nb_of_philosophers, &monitor, &data);
	clean_all(philos, &data);
	return (EXIT_SUCCESS);
}
