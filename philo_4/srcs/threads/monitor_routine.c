/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:02:30 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/04 16:31:15 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>

/**
 * @brief Checks if a philosopher has died from starvation and updates
 * simulation state accordingly.
 *
 * @param data Pointer to the data structure.
 * @param philo Pointer to the philosopher structure being monitored.
 *
 * @return true if the philosopher has died.
 * @return false if the philosopher is still alive.
 */
static bool	death_check_and_update(t_data *data, t_philo *philo)
{
	pthread_mutex_t	*last_meal_mutex;
	pthread_mutex_t	*stop_sim_mutex;

	last_meal_mutex = &philo->last_meal_mutex;
	stop_sim_mutex = &data->stop_sim_mutex;
	pthread_mutex_lock(last_meal_mutex);
	if (get_time_diff_ms(philo->last_meal) >= data->time_to_die)
	{
		pthread_mutex_unlock(last_meal_mutex);
		pthread_mutex_lock(stop_sim_mutex);
		data->stop_sim = true;
		print_log(data->sim_start_time, philo->id, DEATH_MSG,
			&data->print_mutex);
		pthread_mutex_unlock(stop_sim_mutex);
		return (true);
	}
	pthread_mutex_unlock(last_meal_mutex);
	return (false);
}

/**
 * @brief Updates the count of satiated philosophers.
 *
 * @param satiated_philos_counter Pointer to the counter of satiated
 * philosophers.
 * @param remaining_meals Pointer to the number of remaining meals
 * for a philosopher.
 * @param remaining_meals_mutex Mutex to protect access to remaining_meals.
 */
static void	satiaty_counter_update(unsigned int *satiated_philos_counter,
		unsigned int *remaining_meals, pthread_mutex_t *remaining_meals_mutex)
{
	pthread_mutex_lock(remaining_meals_mutex);
	if (*remaining_meals == 0)
		(*satiated_philos_counter)++;
	pthread_mutex_unlock(remaining_meals_mutex);
}

/**
 * @brief Monitors philosophers' status in a loop until all are satiated or
 * death occurs.
 *
 * @param philos Pointer to the array of philosopher structures.
 * @param nb_of_philosophers Total number of philosophers in the simulation.
 * @param data Pointer to shared data structure.
 */
static void	monitor_checking_loop(t_philo *philos,
		unsigned int nb_of_philosophers, t_data *data)
{
	unsigned int	satiated_philos_counter;
	t_philo			*philos_first_elt;

	satiated_philos_counter = 0;
	philos_first_elt = philos;
	while (satiated_philos_counter < nb_of_philosophers)
	{
		satiated_philos_counter = 0;
		philos = philos_first_elt;
		while (philos->id != 0)
		{
			if (death_check_and_update(data, philos) == true)
				return ;
			satiaty_counter_update(&satiated_philos_counter,
				&philos->remaining_meals, &philos->remaining_meals_mutex);
			philos++;
			usleep(30);
		}
	}
	protected_bool_update(&data->stop_sim, true, &data->stop_sim_mutex);
	return ;
}

/**
 * @brief Monitor thread routine that oversees philosopher states and simulation
 * end conditions.
 *
 * @param arg Pointer to the array of philosophers (cast from void*).
 * @return NULL upon completion of monitoring duties.
 */
void	*monitor_routine(void *arg)
{
	t_data	*data;
	t_philo	*philos;

	philos = (t_philo *)arg;
	data = philos[0].data;
	monitor_checking_loop(philos, data->nb_of_philosophers, data);
	return (NULL);
}
