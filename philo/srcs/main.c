/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:50:19 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/04 18:55:44 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
	t_config config;

	if (ac < 4 || ac > 5)
	{
		printf("Error : Wrong number of arguments\n");
		return(EXIT_SUCCESS);
	}
	if (initialize_user_config(av, &config) == NULL)
	{
		printf("Error : Wrong argument format\n");
		return(EXIT_SUCCESS);
	}
	if (initialize_config(&config))
}
