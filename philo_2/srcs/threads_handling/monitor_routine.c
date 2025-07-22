/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:42:11 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/22 18:47:02 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <unistd.h>

// bool single_philo_death_check(t_philo *philo, t_config *config)
// {
// 	pthread_mutex_lock(&philo->last_meal_mutex);
// 	if (get_time_diff_ms(philo->last_meal) >= config->time_to_die)
// 	{
// 		protected_log_print(get_time_diff_ms(config->sim_start_time),
// 			philo->id, DEATH_MSG, config);
// 		pthread_mutex_unlock(&philo->last_meal_mutex);
// 		return (true);
// 	}
// 	pthread_mutex_unlock(&philo->last_meal_mutex);
// 	return (false);
// }

// bool all_philos_death_check(t_philo *philos, t_config *config)
// {
//     unsigned int i;

//     i = 0;
//     while (i < config->number_of_philosophers)
//     {
//         if (single_philo_death_check(&philos[i], config) == true)
//             return (true);
//         i++;
//     }
//     return (false);
// }

// bool sim_must_stop(t_philo *philos, t_config *config)
// {
// 	unsigned int i;
// 	unsigned int satiated_philos;

// 	satiated_philos = 0;
// 	i = 0;
// 	while (i < config->number_of_philosophers)
// 	{
// 		if (single_philo_death_check(&philos[i], config) == true)
//             return (true);
// 		pthread_mutex_lock(&philos[i].nb_of_meals_mutex);
// 		if (philos[i].nb_of_meals >= config->number_of_times_each_philosopher_must_eat)
// 			satiated_philos++;
// 		pthread_mutex_unlock(&philos[i].nb_of_meals_mutex);
// 		i++;
// 	}
// 	if (satiated_philos == config->number_of_philosophers)
// 		return (true);
// 	return (false);
// }

// bool sim_must_stop(t_philo *philos, t_config *config)
// {
//     unsigned int i = 0;
//     unsigned int satiated_philos = 0;

//     // PRIORITY 1: Check for death FIRST
//     while (i < config->number_of_philosophers)
//     {
//         if (single_philo_death_check(&philos[i], config) == true)
//             return (true);
//         i++;
//     }

//    
	// PRIORITY 2: Only check meals if no death occurred AND meal limit is set
//     if (config->number_of_times_each_philosopher_must_eat != NO_ARG)
//     {
//         i = 0;
//         while (i < config->number_of_philosophers)
//         {
//             pthread_mutex_lock(&philos[i].nb_of_meals_mutex);
//             if (philos[i].nb_of_meals >= config->number_of_times_each_philosopher_must_eat)
//                 satiated_philos++;
//             pthread_mutex_unlock(&philos[i].nb_of_meals_mutex);
//             i++;
//         }

//         if (satiated_philos == config->number_of_philosophers)
//             return (true);
//     }

//     return (false);
// }

// // void	*monitor_routine(void *arg)
// // {
// // 	t_philo			*philos;
// // 	t_config		*config;

// // 	philos = (t_philo *)arg;
// // 	config = philos[0].config;
// // 	while (1)
// // 	{
// // 		if (protected_bool_check(config->stop_sim,
// 				config->stop_sim_mutex) == true)
// // 			break ;
// // 		// if (all_philos_death_check(philos, config) == true)
// // 		// {
// // 		// 	protected_bool_update(&config->stop_sim, true,
// 				config->stop_sim_mutex);
// // 		// 	break ;
// // 		// }
// // 		if (sim_must_stop(philos, config) == true)
// // 		{
// // 			protected_bool_update(&config->stop_sim, true,
// 				config->stop_sim_mutex);
// // 			break ;
// // 		}
// // 		usleep(1000);
// // 	}
// // 	return (NULL);
// // }

bool	philo_death_check(t_philo *philos, t_config *config)
{
	unsigned int	i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		pthread_mutex_lock(&philos[i].last_meal_mutex);
		if (get_time_diff_ms(philos[i].last_meal) >= config->time_to_die)
		{
			pthread_mutex_unlock(&philos[i].last_meal_mutex);
			protected_log_print(get_time_diff_ms(config->sim_start_time),
				philos[i].id, DEATH_MSG, config);
			protected_bool_update(&config->stop_sim, true,
				config->stop_sim_mutex);
			return (true);
		}
		pthread_mutex_unlock(&philos[i].last_meal_mutex);
		i++;
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_philo		*philos;
	t_config	*config;

	philos = (t_philo *)arg;
	config = philos[0].config;
	while (1)
	{
		if (philo_death_check(philos, config) == true)
			break ;
        if (config->number_of_times_each_philosopher_must_eat != NO_ARG)
        {
		    pthread_mutex_lock(&config->satiated_philos_counter_mutex);
		    pthread_mutex_lock(&config->stop_sim_mutex);
		    if (config->satiated_philos_counter >= config->number_of_philosophers)
		    {
			    config->stop_sim = true;
			    pthread_mutex_unlock(&config->satiated_philos_counter_mutex);
			    pthread_mutex_unlock(&config->stop_sim_mutex);
			    break ;
		    }
		pthread_mutex_unlock(&config->satiated_philos_counter_mutex);
		pthread_mutex_unlock(&config->stop_sim_mutex);
        }
        usleep(1000);
	}
	return (NULL);
}
