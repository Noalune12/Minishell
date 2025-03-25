#include <signal.h>

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
