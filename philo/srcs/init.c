/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:50:42 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/04 19:03:40 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*initialize_user_config(char *user_input[], t_config *config)
{
	long	nb;
	int		i;

	i = 1;
	while (i <= 4 || (i == 5 && user_input[5] != NULL))
	{
		nb = check_and_convert_to_long(user_input[i]);
		if (nb < 0)
			return (NULL);
		if (i == 1)
			config->number_of_philosophers = nb;
		else if (i == 2)
			config->time_to_die = nb;
		else if (i == 3)
			config->time_to_eat = nb;
		else if (i == 4)
			config->time_to_sleep = nb;
		else if (i == 5)
			config->number_of_times_each_philosopher_must_eat = nb;
		i++;
	}
	return (config);
}

void	*initialize_config(char *user_input[], t_config *config)
{
	if (initialize_user_config(user_input, config) == NULL)
	{
		printf("Error : Wrong argument format\n");
		return (NULL);
	}
	config->fork = malloc((config->number_of_philosophers + 1)
			* sizeof(pthread_mutex_t));
	if (config->fork == NULL)
	{
		printf("Error : malloc failed during fork[] initialization\n");
		return (NULL);
	}
}

void	initialize_philo(void)
{
}