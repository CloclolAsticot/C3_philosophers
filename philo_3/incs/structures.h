/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:35:54 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/22 16:12:13 by csavreux         ###   ########lyon.fr   */
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
	unsigned int	satiated_philos_counter;
	pthread_mutex_t	satiated_philos_counter_mutex;
	pthread_mutex_t	print_mutex;
	bool			stop_sim;
	pthread_mutex_t	stop_sim_mutex;

}					t_config;

typedef struct s_philo
{
	unsigned int	id;
	long			last_meal;
	t_fork			*left_fork;
	t_fork			*right_fork;
	unsigned int	nb_of_meals;
	bool			is_satiated;
	pthread_t		thread_id;
	t_config		*config;
}					t_philo;

#endif