/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:35:54 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/04 18:56:39 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_config
{
	long			sim_start_time;
	long			number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print_mutex;
	bool			has_a_philo_died;
}					t_config;

typedef struct s_philo
{
	int				id;
	int				last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				nb_of_meals;
	pthread_t		thread_id;
	t_config		*config;
}					t_philo;

long				check_and_convert_to_long(char *str_to_convert);

void				*initialize_user_config(char *user_input[],
						t_config *config);

#endif