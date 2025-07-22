/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_initialization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:28:32 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/22 16:54:44 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * @brief Initializes an array of philosopher structures with their initial 
 * values.
 * 
 * @param philos Pointer to the array of philosopher structures to initialize.
 * @param config Pointer to the configuration structure containing simulation 
 * 				 parameters.
 */
void	*initialize_philos(t_config *config)
{
	t_philo *philos;
	unsigned int	i;

	philos = malloc((config->number_of_philosophers) * sizeof(t_philo));
	if (philos == NULL)
	{
		printf("Error : malloc failed for philos[]\n");
		clean_all(NULL, config);
		return (NULL);
	}
	memset(philos, 0, (config->number_of_philosophers) * sizeof(t_philo));
	i = 0;
	while (i < config->number_of_philosophers)
	{
		philos[i].id = i + 1;	// init ID
		philos[i].left_fork = &(config->forks[i]);	// init left fork
		philos[i].right_fork = &(config->forks[(i + 1)	// init right fork
				% config->number_of_philosophers]);
		philos[i].nb_of_meals = 0;	// init nb of meals
		philos[i].config = config;	// init config (so each philo has its informations)
		philos[i].last_meal = config->sim_start_time;	// init last meal time
		philos[i].is_satiated = false;
		i++;
	}
	return (philos);
}


