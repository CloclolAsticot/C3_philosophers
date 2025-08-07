/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:39:19 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/07 10:59:21 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

/**
 * @brief Calculates the length of a null-terminated string.
 *
 * @param str Pointer to the null-terminated string to measure.
 * @return size_t The length of the string (number of characters before '\0').
 */
size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/**
 * @brief Prints an error message to standard error output.
 * 
 * @param str The error message string to be printed to stderr.
 */
void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

/**
 * @brief Prints an error message to stderr in a thread-safe manner.
 *
 * @param str The error message string to be printed to stderr.
 * @param print_mutex Pointer to the mutex used for synchronizing print 
 * operations.
 */
void	protected_print_error(char *str, pthread_mutex_t *print_mutex)
{
	pthread_mutex_lock(print_mutex);
	print_error(str);
	pthread_mutex_unlock(print_mutex);
}

/**
 * @brief Thread-safe boolean value update function.
 * 
 * @param bool_to_update Pointer to the boolean variable to be updated.
 * @param updated_value The new boolean value to assign.
 * @param bool_mutex Pointer to the mutex used for thread synchronization.
 */
void	protected_bool_update(bool *bool_to_update, bool updated_value,
		pthread_mutex_t *bool_mutex)
{
	pthread_mutex_lock(bool_mutex);
	*bool_to_update = updated_value;
	pthread_mutex_unlock(bool_mutex);
}
