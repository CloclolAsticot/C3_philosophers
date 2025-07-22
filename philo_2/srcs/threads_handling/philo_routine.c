/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:38:20 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/22 19:10:50 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <pthread.h>
#include <unistd.h>

static void	fork_grabbing_attempt(t_fork *first_fork, t_fork *second_fork,
		bool *successful_attempt)
{
	pthread_mutex_lock(&first_fork->fork_mutex);
	if (first_fork->is_fork_used == false)
	{
		first_fork->is_fork_used = true;
		pthread_mutex_unlock(&first_fork->fork_mutex);
		pthread_mutex_lock(&second_fork->fork_mutex);
		if (second_fork->is_fork_used == false)
		{
			second_fork->is_fork_used = true;
			pthread_mutex_unlock(&second_fork->fork_mutex);
			*successful_attempt = true;
		}
		else
		{
			pthread_mutex_unlock(&second_fork->fork_mutex);
			pthread_mutex_lock(&first_fork->fork_mutex);
			first_fork->is_fork_used = false;
			pthread_mutex_unlock(&first_fork->fork_mutex);
		}
	}
	else
		pthread_mutex_unlock(&first_fork->fork_mutex);
}

static bool	take_forks(unsigned int philo_id, t_fork *left_fork,
		t_fork *right_fork, t_config *config)
{
	bool	successful_attempt;

	successful_attempt = false;
	while (protected_bool_check(config->stop_sim,
			config->stop_sim_mutex) == false && successful_attempt == false)
	{
		if (philo_id % 2 == 0)
			fork_grabbing_attempt(left_fork, right_fork, &successful_attempt);
		else if (philo_id % 2 != 0)
			fork_grabbing_attempt(right_fork, left_fork, &successful_attempt);
		if (successful_attempt == false)
			usleep(1000); // 1ms delay
		if (successful_attempt == true)
			break;
	}
	return (successful_attempt);
}

void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_config *config = philo->config;
	bool has_max_meal = false;

	protected_log_print(get_time_diff_ms(config->sim_start_time), philo->id,
			THINK_MSG, config);
	while (protected_bool_check(config->stop_sim,
			config->stop_sim_mutex) == false)
	{
		// Take forks
		if (take_forks(philo->id, philo->left_fork, philo->right_fork,
				config) == false)
			break ;
		// Check death after fork acquisition
		if (protected_bool_check(config->stop_sim,
				config->stop_sim_mutex) == true)
			break ;

		// Rest of your eating logic...
		protected_log_print(get_time_diff_ms(config->sim_start_time), philo->id,
			FORK_MSG, config);
		protected_log_print(get_time_diff_ms(config->sim_start_time), philo->id,
			FORK_MSG, config);
		protected_log_print(get_time_diff_ms(config->sim_start_time), philo->id,
			EAT_MSG, config);
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal = get_current_time_ms();
		pthread_mutex_unlock(&philo->last_meal_mutex);
		pthread_mutex_lock(&config->satiated_philos_counter_mutex);
		(philo->nb_of_meals)++;
		if (config->number_of_times_each_philosopher_must_eat != NO_ARG
			&& philo->nb_of_meals == config->number_of_times_each_philosopher_must_eat
			&& has_max_meal == false)
		{
			has_max_meal = true;
			config->satiated_philos_counter++;
		}
		pthread_mutex_unlock(&config->satiated_philos_counter_mutex);
		if (protected_bool_check(config->stop_sim,
				config->stop_sim_mutex) == true)
			break ;
		usleep(config->time_to_eat * 1000);

		// Put down forks
		protected_bool_update(&philo->left_fork->is_fork_used, false,
			philo->left_fork->fork_mutex);
		protected_bool_update(&philo->right_fork->is_fork_used, false,
			philo->right_fork->fork_mutex);
		protected_log_print(get_time_diff_ms(config->sim_start_time), philo->id,
			SLEEP_MSG, config);
		usleep(config->time_to_sleep * 1000);
		protected_log_print(get_time_diff_ms(config->sim_start_time), philo->id,
			THINK_MSG, config);
		// usleep(1000);
	}
	return (NULL);
}