/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:38:20 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/17 17:52:24 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <pthread.h>
#include <unistd.h>

static bool	check_routine_conditions(bool *has_a_philo_died,
		pthread_mutex_t death_bool_mutex)
{
	if (protected_bool_check(*has_a_philo_died, death_bool_mutex) == true)
		return (true);
	else
		return (false);
}

static bool fork_grabbing_attempt(unsigned int philo_id, t_fork *left_fork,
		t_fork *right_fork)
{
	if (philo_id % 2 == 0)
	{
		if (protected_bool_check(left_fork->is_fork_used,
				left_fork->fork_mutex) == false)
		{
			protected_bool_update(&left_fork->is_fork_used, true, left_fork->fork_mutex);
			if (protected_bool_check(right_fork->is_fork_used,
				right_fork->fork_mutex) == false)
			{
				protected_bool_update(&right_fork->is_fork_used, true, right_fork->fork_mutex);
				return (true);
			}
			else
			 	protected_bool_update(&left_fork->is_fork_used, false, left_fork->fork_mutex);
		}
	}
	if (philo_id % 2 != 0)
	{
		if (protected_bool_check(right_fork->is_fork_used,
				right_fork->fork_mutex) == false)
		{
			protected_bool_update(&right_fork->is_fork_used, true, right_fork->fork_mutex);
			if (protected_bool_check(left_fork->is_fork_used,
				left_fork->fork_mutex) == false)
			{
				protected_bool_update(&left_fork->is_fork_used, true, left_fork->fork_mutex);
				return (true);
			}
			else
			 	protected_bool_update(&right_fork->is_fork_used, false, right_fork->fork_mutex);
		}
	}
	return(false);
}

static bool take_forks(unsigned int philo_id, t_fork *left_fork,
		t_fork *right_fork, t_config *config)
{
	bool has_attempt_been_successful;

	has_attempt_been_successful = false;
	while (protected_bool_check(config->has_a_philo_died, config->death_bool_mutex) == false && has_attempt_been_successful == false)
	{
		has_attempt_been_successful = fork_grabbing_attempt(philo_id, left_fork, right_fork);
	}
	return (has_attempt_been_successful);
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
	while (protected_bool_check(*has_a_philo_died,
			config->death_bool_mutex) == false)
	{
		if (check_routine_conditions(has_a_philo_died,
				config->death_bool_mutex) == true)
			break ;
		print_log(get_time_diff_ms(config->sim_start_time), philo->id, THINK_MSG,
			config);
		// Take forks
		if (take_forks(philo->id, philo->left_fork, philo->right_fork, config) == false)
			break; // ---> faire une boucle pour pas bloquer
		print_log(get_time_diff_ms(config->sim_start_time), philo->id, FORK_MSG,
			config);
		print_log(get_time_diff_ms(config->sim_start_time), philo->id, FORK_MSG,
			config);
		// Eat
		if (check_routine_conditions(has_a_philo_died,
				config->death_bool_mutex) == true)
			break ;
		print_log(get_time_diff_ms(config->sim_start_time), philo->id, EAT_MSG,
			config);
		*last_meal_time = get_current_time_ms();
		(*nb_of_meals)++;
		usleep(config->time_to_eat * 1000);
		// Put down forks
		protected_bool_update(&philo->left_fork->is_fork_used, false, philo->left_fork->fork_mutex);
		protected_bool_update(&philo->right_fork->is_fork_used, false, philo->right_fork->fork_mutex);
		if (check_routine_conditions(has_a_philo_died,
				config->death_bool_mutex) == true)
			break ;
		// Sleep
		if (check_routine_conditions(has_a_philo_died,
				config->death_bool_mutex) == true)
			break ;
		print_log(get_time_diff_ms(config->sim_start_time), philo->id, SLEEP_MSG,
			config);
		usleep(config->time_to_sleep * 1000);
	}
	return (NULL);
}
