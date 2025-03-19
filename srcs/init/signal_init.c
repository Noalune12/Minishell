#include "minishell.h"
#include <signal.h>

int	g_signal_received = 0;

void	signal_handler(int signum) //ctrl c
{
	rl_done = 1;
	g_signal_received = signum;
	if (signum == SIGPIPE)
	{
		g_signal_received = SIGPIPE;
	}
}

void	handle_signal_main(void)
{
	struct sigaction	s_sigaction;

	g_signal_received = 0;
	ft_memset(&s_sigaction, 0, sizeof(s_sigaction));
	s_sigaction.sa_flags = SA_RESTART;
	sigemptyset(&s_sigaction.sa_mask);
	sigaddset(&s_sigaction.sa_mask, SIGINT);
	sigaddset(&s_sigaction.sa_mask, SIGQUIT);
	sigaddset(&s_sigaction.sa_mask, SIGPIPE);
	s_sigaction.sa_handler = signal_handler;
	sigaction(SIGINT, &s_sigaction, NULL);
	s_sigaction.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s_sigaction, NULL);
	sigaction(SIGPIPE, &s_sigaction, NULL);
}


void	signal_handler_exec(int signum)
{
	g_signal_received = signum;
}

void	handle_signal_child(void)
{
	struct sigaction	s_sigaction;

	// g_signal_received = 0;
	ft_memset(&s_sigaction, 0, sizeof(s_sigaction));
	s_sigaction.sa_handler = SIG_DFL;
	sigemptyset(&s_sigaction.sa_mask);
	sigaddset(&s_sigaction.sa_mask, SIGINT);
	sigaddset(&s_sigaction.sa_mask, SIGQUIT);
	sigaction(SIGINT, &s_sigaction, NULL);
	sigaction(SIGQUIT, &s_sigaction, NULL);
	// s_sigaction.sa_flags = SA_RESTART; // mais pourquoi ??
	// s_sigaction.sa_handler = &signal_handler_exec;
	// sigaction(SIGINT, &s_sigaction, NULL);
	// sigaction(SIGQUIT, &s_sigaction, NULL);
}

void	handle_signal_wait(void)
{
	struct sigaction	s_sigaction;

	g_signal_received = 0;
	sigemptyset(&s_sigaction.sa_mask);
	s_sigaction.sa_flags = SA_RESTART; // mais pourquoi ??
	sigaddset(&s_sigaction.sa_mask, SIGINT);
	sigaddset(&s_sigaction.sa_mask, SIGQUIT);
	sigaddset(&s_sigaction.sa_mask, SIGPIPE);
	s_sigaction.sa_handler = &signal_handler_exec;
	sigaction(SIGINT, &s_sigaction, NULL);
	sigaction(SIGQUIT, &s_sigaction, NULL);
	sigaction(SIGPIPE, &s_sigaction, NULL);
}

int	return_global(void)
{
	return (g_signal_received);
}

void	init_global(void)
{
	g_signal_received = 0;
}
