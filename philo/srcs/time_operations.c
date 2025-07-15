/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:23:54 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/15 18:44:27 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stddef.h>

long get_current_time_ms(void)
{
	struct timeval time_struct;
	long time_in_ms;

	gettimeofday(&time_struct, NULL);
	time_in_ms = time_struct.tv_sec * 1000 + time_struct.tv_usec;
	return (time_in_ms);
}

long get_time_diff_ms(long old_time)
{
	long current_time;
	long time_diff;

	current_time = get_current_time_ms();
	time_diff = current_time - old_time;
	return (time_diff);
}
