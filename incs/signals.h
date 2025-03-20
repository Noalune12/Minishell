#ifndef SIGNALS_H
# define SIGNALS_H

void	signal_handler(int signum);
void	handle_signal_main(void);
void	handle_signal_child(void);
void	handle_signal_wait(void);
void	init_global(void);

int		return_global(void);

#endif
