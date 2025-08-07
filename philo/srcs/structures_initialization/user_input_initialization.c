/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input_initialization.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:57:44 by csavreux          #+#    #+#             */
/*   Updated: 2025/08/04 16:30:34 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <limits.h>

/**
 * @brief Checks if a character is a digit (0-9).
 *
 * @param character The character to check (passed as int to match standard
 * library convention).
 * @return true if the character is a digit ('0' through '9'), false otherwise.
 */
static bool	ft_isdigit(int character)
{
	if (character >= '0' && character <= '9')
		return (true);
	else
		return (false);
}

/**
 * @brief Checks if the given string represents a valid number.
 *
 * @param str The input string to be checked.
 * @return Returns true if the string is a valid number, false otherwise.
 */
static bool	is_number(char *str)
{
	if (ft_strlen(str) == 0)
		return (false);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

/**
 * @brief Converts a string to an unsigned integer with overflow protection.
 * Overflows if the given number > UINT_MAX / 1000 - specifity for the philos
 * project.
 *
 * @param str Pointer to the null-terminated string to be converted.
 *
 * @return On success, returns the converted unsigned integer value.
 * @return On positive overflow or if the given number is < 0, returns UINT_MAX.
 */
static unsigned int	ft_atouint_philo(const char *str)
{
	size_t	i;
	long	nbr;

	i = 0;
	nbr = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (WRONG_FORMAT_NB);
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (nbr > ((UINT_MAX / 1000 - (str[i] - '0')) / 10))
			return (WRONG_FORMAT_NB);
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr);
}

/**
 * @brief Ensures a string is convertible to unsigned int and converts it.
 *
 * @param str_to_convert The string to validate and convert.
 *
 * @return On success, returns the converted positive unsigned integer.
 * @return On failure, returns -1.
 */
unsigned int	check_and_convert_user_input(char *str_to_convert)
{
	long	nb;

	if (is_number(str_to_convert) == false)
		return (WRONG_FORMAT_NB);
	nb = ft_atouint_philo(str_to_convert);
	return (nb);
}
