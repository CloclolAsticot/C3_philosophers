/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:59:56 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/16 16:59:33 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include <stdio.h>

void print_log(long timestamp, long philo_id, char *msg, t_config *config)
{
	pthread_mutex_lock(&config->print_mutex);
	printf("%ld %ld %s\n", timestamp, philo_id, msg);
	pthread_mutex_unlock(&config->print_mutex);
}
