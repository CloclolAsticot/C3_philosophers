/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:59:56 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/17 17:12:38 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include <stdio.h>

void	print_log(unsigned int timestamp, unsigned int philo_id, char *msg,
		t_config *config)
{
	pthread_mutex_lock(&config->print_mutex);
	if (config->has_a_philo_died == false)
	{
		printf("%u %u %s\n", timestamp, philo_id, msg);
		// fflush(stdout);
	}
	pthread_mutex_unlock(&config->print_mutex);
}
