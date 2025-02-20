#include "minishell.h"

int	g_signal_received;

void	signal_handler(int signum) //ctrl c
{
	if (signum == SIGINT)
	{
		g_signal_received = SIGINT;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	g_signal_received = SIGQUIT;
}
