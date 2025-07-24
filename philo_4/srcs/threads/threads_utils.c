/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:32:59 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/24 16:43:55 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "threads_handling.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

void create_philo_threads(t_philo *philos, t_data *data)
{
	unsigned int i;
	unsigned int nb_of_philos;

	nb_of_philos = data->nb_of_philosophers;
	i = 0;
	while (i < nb_of_philos)
	{
		pthread_create(&philos[i].thread_id, NULL, &philo_routine, &philos[i]);
		i++;
	}
}

void	terminate_threads(t_philo *philos, t_data *data)
{
	unsigned int	i;
	unsigned int	nb_of_philosophers;

	nb_of_philosophers = data->nb_of_philosophers;
	i = 0;
	while (i < nb_of_philosophers)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
}

