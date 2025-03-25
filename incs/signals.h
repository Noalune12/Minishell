#ifndef SIGNALS_H
# define SIGNALS_H

extern int	g_signal_received;

void	signal_handler_exec(int signum);
void	handle_signal_main(void);
void	handle_signal_child(void);
void	handle_signal_wait(void);
void	init_global(void);

int		return_global(void);
int		event(void);

#endif
