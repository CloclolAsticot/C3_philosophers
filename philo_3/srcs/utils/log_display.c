/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:59:56 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/22 14:12:44 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include <stdio.h>

void	protected_log_print(unsigned int timestamp, unsigned int philo_id, char *msg,
        t_config *config)
{
    pthread_mutex_lock(&config->stop_sim_mutex);
    if (config->stop_sim == false)
    {
        pthread_mutex_lock(&config->print_mutex);
        printf("%u %u %s\n", timestamp, philo_id, msg);
        pthread_mutex_unlock(&config->print_mutex);
    }
	pthread_mutex_unlock(&config->stop_sim_mutex);
}

void	protected_print(char *msg, t_config *config)
{
    pthread_mutex_lock(&config->stop_sim_mutex);
    if (config->stop_sim == false)
    {
        pthread_mutex_lock(&config->print_mutex);
        printf("%s\n", msg);
        pthread_mutex_unlock(&config->print_mutex);
    }
	pthread_mutex_unlock(&config->stop_sim_mutex);
}