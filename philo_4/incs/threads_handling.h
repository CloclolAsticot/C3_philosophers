/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_handling.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:35:38 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/03 19:04:30 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_HANDLING_H
# define THREADS_HANDLING_H

# include "structures.h"

void	*create_philo_threads(t_philo *philos, unsigned int nb_of_philos,
			t_data *data);

void	*create_monitor_thread(pthread_t *monitor, t_philo *philos,
			t_data *data);

void	terminate_philo_threads(t_philo *philos, unsigned int nb_of_threads,
			t_data *data);

void	terminate_all_threads(t_philo *philos, unsigned int nb_of_philo_threads,
			pthread_t *monitor, t_data *data);

void	*monitor_routine(void *arg);

void	*philo_routine_even(void *arg);

void	*philo_routine_odd(void *arg);

// Philo Routine Utils

bool	stop_sim_check(bool *stop_sim, pthread_mutex_t *stop_sim_mutex);

bool	grab_both_forks(t_fork *left_fork, t_fork *right_fork, t_philo *philo,
			t_data *data);

// bool	grab_both_forks(t_philo *philo, t_fork *left_fork, t_fork *right_fork,
// 			t_data *data);

void	protected_bool_update(bool *bool_to_update, bool updated_value,
			pthread_mutex_t *bool_mutex);

#endif