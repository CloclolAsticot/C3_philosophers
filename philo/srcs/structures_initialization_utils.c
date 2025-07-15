/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_initialization_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:57:44 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/15 16:50:45 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
 * @brief Converts a string to a long integer with overflow protection.
 *
 * @param str Pointer to the null-terminated string to be converted.
 *
 * @return On success, returns the converted long integer value.
 * @return On positive overflow, returns -1.
 * @return On negative overflow, returns 0.
 */
static long	ft_atol(const char *str)
{
	size_t	i;
	long	sign;
	long	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)) // skips whitespaces
		i++;
	if (str[i] == '-' || str[i] == '+') // checks the sign
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i])) // converts the string
	{
		if (nbr > ((LONG_MAX - (str[i] - '0')) / 10) && sign > 0)
			return (-1);
		else if (nbr > ((LONG_MAX - (str[i] - '0')) / 10) && sign < 0)
			return (0);
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (sign * nbr); // returns the conversion result (with the right sign)
}

/**
 * @brief Ensures a string is convertible to long and converts it.
 *
 * @param str_to_convert The string to validate and convert.
 *
 * @return On success, returns the converted positive long integer.
 * @return On failure, returns -1.
 */
long	check_and_convert_user_input(char *str_to_convert)
{
	long	nb;

	if (is_number(str_to_convert) == false)
		// checks if the input str is a number
		return (-1);
	if (str_to_convert[0] == '-') // checks if the input str is < 0
		return (-1);
	nb = ft_atol(str_to_convert); // converts the input str to a long
	if (nb < 0)                  
		// checks if there was an overflow (input str is longer than a long)
		return (-1);
	return (nb);
}
