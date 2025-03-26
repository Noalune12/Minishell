/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:18:25 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 09:18:43 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

extern int	g_signal_received;

void	handle_signal_child(void);
void	handle_signal_main(void);
void	handle_signal_wait(void);
void	init_global(void);
void	signal_handler_exec(int signum);

int		event(void);
int		return_global(void);

#endif
