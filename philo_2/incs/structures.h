/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:35:54 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/17 17:38:26 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_fork
{
	bool			is_fork_used;
	pthread_mutex_t	fork_mutex;
}					t_fork;

typedef struct s_config
{
	long			sim_start_time;
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_times_each_philosopher_must_eat;
	t_fork			*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_bool_mutex;
	bool			has_a_philo_died;
	pthread_mutex_t	min_meals_mutex;
	bool			enough;
}					t_config;

typedef struct s_philo
{
	unsigned int	id;
	long			last_meal_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	unsigned int	nb_of_meals;
	pthread_t		thread_id;
	t_config		*config;
}					t_philo;

#endif