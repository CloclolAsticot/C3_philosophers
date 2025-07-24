/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:42:11 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/16 18:03:24 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

bool	check_routine_conditions(bool *has_a_philo_died, pthread_mutex_t death_bool_mutex)
{
	if (protected_bool_check(*has_a_philo_died, death_bool_mutex) == true)
		return (true);
	else
		return (false);
}

void	take_forks(t_philo *philo, t_config *config)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_log(get_time_diff_ms(config->sim_start_time), philo->id, FORK_MSG,
			config);
		pthread_mutex_lock(philo->right_fork);
		print_log(get_time_diff_ms(config->sim_start_time), philo->id, FORK_MSG,
			config);
	}
	else if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_log(get_time_diff_ms(config->sim_start_time), philo->id, FORK_MSG,
			config);
		pthread_mutex_lock(philo->left_fork);
		print_log(get_time_diff_ms(config->sim_start_time), philo->id, FORK_MSG,
			config);
	}
}

void	terminate_threads(t_philo *philos, t_config *config)
{
	unsigned int	i;
	unsigned int	nb_of_philosophers;

	nb_of_philosophers = config->number_of_philosophers;
	i = 0;
	while (i < nb_of_philosophers)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
}

void	*monitor_routine(void *arg)
{
	t_philo			*philos;
	t_config		*config;
	unsigned int	number_of_required_meals;
	bool			min_meals_nb_reached;
	long			i;

	philos = (t_philo *)arg;
	config = philos[0].config;
	number_of_required_meals = config->number_of_required_meals;
	min_meals_nb_reached = true;
	while (protected_bool_check(config->has_a_philo_died, config->death_bool_mutex) == false)
	{
		i = 0;
		min_meals_nb_reached = true;
		while (i < config->number_of_philosophers)
		{
			if (number_of_required_meals != NO_ARG)
				if (philos[i].nb_of_meals < number_of_required_meals)
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
			|| (number_of_required_meals != NO_ARG
				&& min_meals_nb_reached == true))
			break ;
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	t_config		*config;
	bool			*has_a_philo_died;
	unsigned int	*nb_of_meals;
	long			*last_meal_time;

	philo = (t_philo *)arg;
	has_a_philo_died = &philo->config->has_a_philo_died;
	nb_of_meals = &philo->nb_of_meals;
	last_meal_time = &philo->last_meal_time;
	config = philo->config;
	while (protected_bool_check(*has_a_philo_died, config->death_bool_mutex) == false)
	{
		if (check_routine_conditions(has_a_philo_died, config->death_bool_mutex) == true)
			break ;
		print_log(get_time_diff_ms(config->sim_start_time), philo->id,
			THINK_MSG, config);
		// Take forks
		take_forks(philo, config);	// ---> faire une boucle pour pas bloquer
		// Eat
		if (check_routine_conditions(has_a_philo_died, config->death_bool_mutex) == true)
			break ;
		print_log(get_time_diff_ms(config->sim_start_time), philo->id, EAT_MSG,
			config);
		*last_meal_time = get_current_time_ms();
		(*nb_of_meals)++;
		usleep(config->time_to_eat * 1000);
		// Put down forks
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (check_routine_conditions(has_a_philo_died, config->death_bool_mutex) == true)
			break ;
		// Sleep
		if (check_routine_conditions(has_a_philo_died, config->death_bool_mutex) == true)
			break ;
		print_log(get_time_diff_ms(config->sim_start_time), philo->id,
			SLEEP_MSG, config);
		usleep(config->time_to_sleep * 1000);
	}
	return (NULL);
}
