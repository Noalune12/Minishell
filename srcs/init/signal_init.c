#include "minishell.h"

int	g_signal_received = 0;

void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_received = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO); // a degager, tres tres mauvaise pratique
	}
}

void	signal_handler(int signum) //ctrl c
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal_received = SIGINT;
	}
	else if (signum == SIGQUIT)
		g_signal_received = SIGQUIT;
}

// void	signal_handler_exec(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		g_signal_received = SIGINT;
// 	}
// 	else if (signum == SIGQUIT)
// 		g_signal_received = SIGQUIT;
// }

int	return_global(void)
{
	return (g_signal_received);
}

void	init_global(void)
{
	g_signal_received = 0;
}
