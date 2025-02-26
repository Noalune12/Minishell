#include "minishell.h"

int	g_signal_received = 0;

/**
 * @brief comportement pas vraiment gerer je comprend pas trop comment faore
 *
 */
void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(0);
	}
	g_signal_received = sig;
}

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

int	return_global(void)
{
	return (g_signal_received);
}

void	init_global(void)
{
	g_signal_received = 0;
}
