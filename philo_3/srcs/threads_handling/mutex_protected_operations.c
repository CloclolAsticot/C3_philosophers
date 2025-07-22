/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_protected_operations.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:35:04 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/22 14:28:40 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>

bool protected_bool_check(bool bool_value, pthread_mutex_t bool_mutex)
{
	bool state;
	
	pthread_mutex_lock(&bool_mutex);
	state = bool_value;
	pthread_mutex_unlock(&bool_mutex);
	return (state);
}

void protected_bool_update(bool *bool_to_update, bool updated_value, pthread_mutex_t bool_mutex)
{
	pthread_mutex_lock(&bool_mutex);
	*bool_to_update = updated_value;
	pthread_mutex_unlock(&bool_mutex);
}