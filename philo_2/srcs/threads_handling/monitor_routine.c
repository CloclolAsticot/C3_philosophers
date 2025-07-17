/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:42:11 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/17 17:45:35 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*monitor_routine(void *arg)
{
	t_philo			*philos;
	t_config		*config;
	unsigned int	number_of_times_each_philosopher_must_eat;
	bool			min_meals_nb_reached;
	long			i;

	philos = (t_philo *)arg;
	config = philos[0].config;
	number_of_times_each_philosopher_must_eat = config->number_of_times_each_philosopher_must_eat;
	while (protected_bool_check(config->has_a_philo_died, config->death_bool_mutex) == false && protected_bool_check(config->has_a_philo_died, config->death_bool_mutex) == false)
	{
		i = 0;
		while (i < config->number_of_philosophers)
		{
			if (number_of_times_each_philosopher_must_eat != NO_ARG)
				if (philos[i].nb_of_meals < number_of_times_each_philosopher_must_eat)
					min_meals_nb_reached = false;
			if (get_time_diff_ms(philos[i].last_meal_time) >= config->time_to_die)
			{
				print_log(get_time_diff_ms(config->sim_start_time),
					philos[i].id, DEATH_MSG, config);
				protected_bool_update(&config->has_a_philo_died, true, config->death_bool_mutex);
				break ;
			}
			i++;
		}
		if (protected_bool_check(config->has_a_philo_died, config->death_bool_mutex) == true
			|| (number_of_times_each_philosopher_must_eat != NO_ARG
				&& min_meals_nb_reached == true))
			break ;
	}
	return (NULL);
}

