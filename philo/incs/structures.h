/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:35:54 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/15 16:56:14 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_config
{
	struct timeval	sim_start_time;
	time_t			number_of_philosophers;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	long			number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_mutex;
	bool			has_a_philo_died;
}					t_config;

typedef struct s_philo
{
	long			id;
	struct timeval	last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			nb_of_meals;
	pthread_t		thread_id;
	t_config		*config;
}					t_philo;

#endif