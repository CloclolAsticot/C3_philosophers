/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:23:54 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/04 16:25:08 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/time.h>

/**
 * @brief Gets the current time in milliseconds since Unix epoch
 * 
 * @return long Current time in milliseconds since Unix epoch
 */
long	get_current_time_ms(void)
{
	struct timeval	time_struct;

	gettimeofday(&time_struct, NULL);
	return (time_struct.tv_sec * 1000 + time_struct.tv_usec / 1000);
}

/**
 * @brief Calculates the time difference in milliseconds between current time
 * and a given past time.
 * 
 * @param old_time The reference time in milliseconds to compare against.
 
 * @return long The time difference in milliseconds (current_time - old_time).
 */
long	get_time_diff_ms(long old_time)
{
	long	current_time;

	current_time = get_current_time_ms();
	return (current_time - old_time);
}
