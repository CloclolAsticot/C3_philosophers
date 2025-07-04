/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:57:44 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/04 18:14:21 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <string.h>

// Calculates the length of the string pointed to by str, excluding the
// terminating null byte ('\0').
size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

// Checks for a digit (0 through 9) - Returns a nonzero value if the character
// is a digit, and zero if it is not.
bool	ft_isdigit(int character)
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

// Converts the initial portion of the string pointed to by nptr to int.
long	ft_atol(const char *nptr)
{
	size_t	i;
	long	sign;
	long	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		if (nbr > ((LONG_MAX - (nptr[i] - '0')) / 10) && sign > 0)
			return (-1);
		else if (nbr > ((LONG_MAX - (nptr[i] - '0')) / 10) && sign < 0)
			return (0);
		nbr = nbr * 10 + nptr[i] - '0';
		i++;
	}
	return (sign * nbr);
}

long	check_and_convert_to_long(char *str_to_convert)
{
	long nb;

	if (is_number(str_to_convert) == false)
		return (-1);
	if (str_to_convert[0] == '-')
		return (-1);
	nb = ft_atol(str_to_convert);
	if (nb < 0)
		return (-1);
	return (nb);
}
