/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_initialization.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csavreux <csavreux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:51:28 by csavreux          #+#    #+#             */
/*   Updated: 2025/07/17 15:28:26 by csavreux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_INITIALIZATION_H
# define STRUCTURES_INITIALIZATION_H

# include "structures.h"

// Config Initialization
void			*initialize_config(char *user_input[], t_config *config);

// Philos Initialization
void			*initialize_philos(t_config *config);

// Structures Initialization Utils
unsigned int	check_and_convert_user_input(char *str_to_convert);

#endif