/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_ending.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:11:51 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/04 19:28:55 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Terminates and waits for all philosopher threads to complete.
 * 
 * @param philos Pointer to array of philosopher structures containing
 * thread IDs.
 * @param nb_of_threads Number of philosopher threads to join.
 * @param data Pointer to shared data structure.
 */
void	terminate_philo_threads(t_philo *philos, unsigned int nb_of_threads,
		t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < nb_of_threads)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
			protected_print_error(THREAD_JOIN_FAIL, &data->print_mutex);
		i++;
	}
}
