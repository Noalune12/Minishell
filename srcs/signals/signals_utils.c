/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:18 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 13:28:42 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	signal_handler_exec(int signum)
{
	g_signal_received = signum;
}

void	init_global(void)
{
	g_signal_received = 0;
}

int	return_global(void)
{
	return (g_signal_received);
}

int	event(void)
{
	return (0);
}
