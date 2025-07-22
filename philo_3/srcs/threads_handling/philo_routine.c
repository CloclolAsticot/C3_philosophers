/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:38:20 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/22 20:12:14 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

bool	sim_end_check(t_philo *philo, t_config *config)
{
	// checks if a philo is dead
	if (protected_bool_check(config->stop_sim, config->stop_sim_mutex) == true)
		return (true);
	// checks if the actual philo is dead and prints the log if needed
	if (get_time_diff_ms(philo->last_meal) >= config->time_to_die)
	{
		protected_log_print(get_time_diff_ms(config->sim_start_time), philo->id,
			DEATH_MSG, config);
		pthread_mutex_lock(&config->stop_sim_mutex);
		config->stop_sim = true;
		pthread_mutex_unlock(&config->stop_sim_mutex);
		return (true);
	}
	// checks if philos have eaten enough
	if (config->number_of_times_each_philosopher_must_eat != NO_ARG)
	{
		pthread_mutex_lock(&config->satiated_philos_counter_mutex);
		if (config->satiated_philos_counter >= config->number_of_philosophers)
		{
			pthread_mutex_lock(&config->stop_sim_mutex);
			config->stop_sim = true;
			pthread_mutex_unlock(&config->stop_sim_mutex);
			pthread_mutex_unlock(&config->satiated_philos_counter_mutex);
			return (true);
		}
		pthread_mutex_unlock(&config->satiated_philos_counter_mutex);
	}
	return (false);
}

// static void	fork_grabbing_attempt(t_fork *first_fork, t_fork *second_fork,
// 		bool *successful_attempt)
// {
// 	pthread_mutex_lock(&first_fork->fork_mutex);
// 	if (first_fork->is_fork_used == false)
// 	{
// 		first_fork->is_fork_used = true;
// 		pthread_mutex_unlock(&first_fork->fork_mutex);
// 		pthread_mutex_lock(&second_fork->fork_mutex);
// 		if (second_fork->is_fork_used == false)
// 		{
// 			second_fork->is_fork_used = true;
// 			pthread_mutex_unlock(&second_fork->fork_mutex);
// 			*successful_attempt = true;
// 		}
// 		else
// 		{
// 			pthread_mutex_unlock(&second_fork->fork_mutex);
// 			pthread_mutex_lock(&first_fork->fork_mutex);
// 			first_fork->is_fork_used = false;
// 			pthread_mutex_unlock(&first_fork->fork_mutex);
// 		}
// 	}
// 	else
// 		pthread_mutex_unlock(&first_fork->fork_mutex);
// }

static bool fork_grabbing_attempt(t_fork *first_fork, t_fork *second_fork,
		t_philo *philo, t_config *config)
{
	bool first_fork_grabbed;
	bool second_fork_grabbed;

	first_fork_grabbed = false;
	second_fork_grabbed = false;
	while (sim_end_check(philo, config) == false && first_fork_grabbed == false)
	{
		pthread_mutex_lock(&first_fork->fork_mutex);
		if (first_fork->is_fork_used == false)
		{
			first_fork->is_fork_used = true;
			first_fork_grabbed = true;
		}
		pthread_mutex_unlock(&first_fork->fork_mutex);
		usleep(100);
	}
	while (sim_end_check(philo, config) == false && second_fork_grabbed == false)
	{
		pthread_mutex_lock(&second_fork->fork_mutex);
		if (second_fork->is_fork_used == false)
		{
			second_fork->is_fork_used = true;
			second_fork_grabbed = true;
		}
		pthread_mutex_unlock(&second_fork->fork_mutex);
		usleep(100);
	}
	return (second_fork_grabbed);
}

static bool	take_forks(unsigned int philo_id, t_fork *left_fork,
		t_fork *right_fork, t_config *config, t_philo *philo)
{
	bool successful_attempt;
	
	successful_attempt = false;
	if (philo_id % 2 == 0)
		successful_attempt = fork_grabbing_attempt(left_fork, right_fork, philo, config);
	else if (philo_id % 2 != 0)
		successful_attempt = fork_grabbing_attempt(right_fork, left_fork, philo, config);
	return (successful_attempt);
}

void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_config *config = philo->config;

	protected_log_print(get_time_diff_ms(config->sim_start_time), philo->id,
		THINK_MSG, config);
	while (sim_end_check(philo, config) == false)
	{
		// Take forks
		if (take_forks(philo->id, philo->left_fork, philo->right_fork, config,
				philo) == false)
			break ;
		// Rest of your eating logic...
		protected_log_print(get_time_diff_ms(config->sim_start_time), philo->id,
			FORK_MSG, config);
		if (sim_end_check(philo, config) == true)
			break ;
		protected_log_print(get_time_diff_ms(config->sim_start_time), philo->id,
			FORK_MSG, config);
		if (sim_end_check(philo, config) == true)
			break ;
		protected_log_print(get_time_diff_ms(config->sim_start_time), philo->id,
			EAT_MSG, config);
		if (sim_end_check(philo, config) == true)
			break ;
		philo->last_meal = get_current_time_ms();
		if (sim_end_check(philo, config) == true)
			break ;
		usleep(config->time_to_eat * 1000);
		if (sim_end_check(philo, config) == true)
			break ;
		(philo->nb_of_meals)++;
		if (sim_end_check(philo, config) == true)
			break ;
		if (philo->is_satiated == false
			&& philo->nb_of_meals >= config->number_of_times_each_philosopher_must_eat)
		{
			philo->is_satiated = true;
			pthread_mutex_lock(&config->satiated_philos_counter_mutex);
			config->satiated_philos_counter++;
			pthread_mutex_unlock(&config->satiated_philos_counter_mutex);
		}
		if (sim_end_check(philo, config) == true)
			break ;

		// Put down forks
		protected_bool_update(&philo->left_fork->is_fork_used, false,
			philo->left_fork->fork_mutex);
		if (sim_end_check(philo, config) == true)
			break ;
		protected_bool_update(&philo->right_fork->is_fork_used, false,
			philo->right_fork->fork_mutex);

		// Sleep
		if (sim_end_check(philo, config) == true)
			break ;
		protected_log_print(get_time_diff_ms(config->sim_start_time), philo->id,
			SLEEP_MSG, config);
		if (protected_bool_check(config->stop_sim,
				config->stop_sim_mutex) == true)
			break ;
		usleep(config->time_to_sleep * 1000);
		if (sim_end_check(philo, config) == true)
			break ;
		protected_log_print(get_time_diff_ms(config->sim_start_time), philo->id,
			THINK_MSG, config);
	}
	return (NULL);
}