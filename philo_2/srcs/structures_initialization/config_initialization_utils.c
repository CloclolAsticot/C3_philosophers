/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_initialization_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:57:44 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/17 15:18:38 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <limits.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief Calculates the length of a null-terminated string.
 *
 * @param str Pointer to the null-terminated string to measure.
 * @return size_t The length of the string (number of characters before '\0').
 */
static size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

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
 * @return Returns 1 if the string is a valid number, 0 otherwise.
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
 *
 * @param str Pointer to the null-terminated string to be converted.
 *
 * @return On success, returns the converted unsigned integer value.
 * @return On positive overflow or if the given number is < 0, returns -1.
 */
static unsigned int	ft_atouint(const char *str)
{
	size_t	i;
	unsigned int	nbr;

	i = 0;
	nbr = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)) // skips whitespaces
		i++;
	if (str[i] == '-' || str[i] == '+') // checks the sign
	{
		if (str[i] == '-')
			return (WRONG_FORMAT);
		i++;
	}
	while (ft_isdigit(str[i])) // converts the string
	{
		if (nbr > ((UINT_MAX / 1000 - (str[i] - '0')) / 10)) // unsigned int overflow
			return (WRONG_FORMAT);
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr); // returns the conversion result (with the right sign)
}

/**
 * @brief Ensures a string is convertible to unsigned int and converts it.
 *
 * @param str_to_convert The string to validate and convert.
 *
 * @return On success, returns the converted positive unsigned integer.
 * @return On failure, returns -1.
 */
unsigned int check_and_convert_user_input(char *str_to_convert)
{
	long	nb;

	if (is_number(str_to_convert) == false)
		// checks if the input str is a number
		return (WRONG_FORMAT);
	nb = ft_atouint(str_to_convert); // converts the input str to an unsigned int
	if (nb < 0)
		// checks if there was an overflow (input str is longer than an unsigned int) or if the nb is negative
		return (WRONG_FORMAT);
	return (nb);
}
