/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_handling.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:35:38 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/04 16:28:34 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_HANDLING_H
# define THREADS_HANDLING_H

# include "structures.h"

// Monitor Routine
void	*monitor_routine(void *arg);

// Philo Routine
void	*philo_routine_even(void *arg);

void	*philo_routine_odd(void *arg);

bool	grab_both_forks(t_fork *left_fork, t_fork *right_fork, t_philo *philo,
			t_data *data);

void	put_forks_down(bool *left_fork_status, pthread_mutex_t *left_fork_mutex,
			bool *right_fork_status, pthread_mutex_t *right_fork_mutex);

// Threads Creation
void	*create_philo_threads(t_philo *philos, unsigned int nb_of_philos,
			t_data *data);

void	*create_monitor_thread(pthread_t *monitor, t_philo *philos,
			t_data *data);

// Threads Ending
void	terminate_philo_threads(t_philo *philos, unsigned int nb_of_threads,
			t_data *data);

void	terminate_all_threads(t_philo *philos, unsigned int nb_of_philo_threads,
			pthread_t *monitor, t_data *data);

#endif