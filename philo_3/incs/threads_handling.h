/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_handling.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:43:14 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/22 16:07:41 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_HANDLING_H
# define THREADS_HANDLING_H

# include "structures.h"

// Routines
void	*monitor_routine(void *arg);

void	*philo_routine(void *arg);

// Utils
void	*create_threads(t_philo *philos, t_config *config);

void	terminate_philos_threads(t_philo *philos, unsigned int nb_of_threads);

bool	protected_bool_check(bool bool_value, pthread_mutex_t bool_mutex);

void	protected_bool_update(bool *bool_to_update, bool updated_value,
			pthread_mutex_t bool_mutex);

#endif