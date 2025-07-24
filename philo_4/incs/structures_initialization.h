/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_initialization.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:51:28 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/24 16:42:42 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_INITIALIZATION_H
# define STRUCTURES_INITIALIZATION_H

# include "structures.h"

// Structurs Initialization Utils

unsigned int	check_and_convert_user_input(char *str_to_convert);

// Structure Initialization Functions

void	*initialize_data(char *user_input[], t_data *data);

void	*initialize_philos(t_data *data);

#endif