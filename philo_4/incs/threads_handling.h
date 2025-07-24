/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_handling.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:35:38 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/24 16:42:45 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_HANDLING_H
# define THREADS_HANDLING_H

#include "structures.h"

void create_philo_threads(t_philo *philos, t_data *data);

void	terminate_threads(t_philo *philos, t_data *data);

void	*monitor_routine(void *arg);

void	*philo_routine(void *arg);

#endif