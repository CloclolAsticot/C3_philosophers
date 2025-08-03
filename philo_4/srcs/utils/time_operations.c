/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:23:54 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/03 17:11:24 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stddef.h>

long get_current_time_ms(void)
{
	struct timeval time_struct;

	gettimeofday(&time_struct, NULL);
	return (time_struct.tv_sec * 1000 + time_struct.tv_usec / 1000);
}

long get_time_diff_ms(long old_time)
{
	long current_time;

	current_time = get_current_time_ms();
	return (current_time - old_time);
}
