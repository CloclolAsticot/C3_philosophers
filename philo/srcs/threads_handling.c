/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:42:11 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/15 18:59:32 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include <sys/time.h>

bool check_routine_conditions_and_quit_if_needed(long time_since_last_meal, bool *has_a_philo_died, long time_to_die)
{
	if (*has_a_philo_died == true)
		return (true);
	if (time_since_last_meal >= time_to_die)
	{
		*has_a_philo_died = true;
		
		return (true);
	}
	if ()
	
}



void *philo_routine(void *arg)
{
	t_philo *philo;
	bool *has_a_philo_died;
	long *nb_of_meals;
	long* last_meal_time;

	philo = (t_philo *)arg;
	has_a_philo_died = &philo->config->has_a_philo_died;
	nb_of_meals = &philo->nb_of_meals;
	last_meal_time = &philo->last_meal_time;
	while(1)
	{
		
		if (get_time_diff_ms())
	}
    return (return_value);
}