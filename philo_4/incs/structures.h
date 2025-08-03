/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:35:54 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/03 15:56:24 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_fork
{
	bool 			fork_status;
	pthread_mutex_t fork_mutex;
}					t_fork;

typedef struct s_data
{
	long			sim_start_time;
	unsigned int	nb_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	nb_of_required_meals;
	t_fork			*forks;
	pthread_mutex_t	print_mutex;
	bool			stop_sim;
	pthread_mutex_t stop_sim_mutex;

}					t_data;

typedef struct s_philo
{
	unsigned int	id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	long			last_meal;
	pthread_mutex_t	last_meal_mutex;
	unsigned int	remaining_meals;
	pthread_mutex_t	remaining_meals_mutex;
	pthread_t		thread_id;
	t_data			*data;
}					t_philo;





#endif