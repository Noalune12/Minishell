#include "minishell.h"
#include <signal.h>

int	g_signal_received = 0;

// void	heredoc_signal_handler(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		g_signal_received = SIGINT;
// 		rl_replace_line("", 0);
// 		rl_done = 1;

// 		// close(STDIN_FILENO); // a degager, tres tres mauvaise pratique
// 	}
// }

void	signal_handler(int signum) //ctrl c
{
	// if (signum == SIGINT)
	// {
	rl_done = 1;
	// printf("\n");
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
	g_signal_received = signum;
	// rl_done = 1;
	// 	g_signal_received = SIGINT;
	// }
	// else if (signum == SIGQUIT)
	// 	g_signal_received = SIGQUIT;
}

void	handle_signal_main(void)
{
	struct sigaction	s_sigaction;

	g_signal_received = 0;
	s_sigaction.sa_flags = SA_RESTART;
	sigemptyset(&s_sigaction.sa_mask);
	sigaddset(&s_sigaction.sa_mask, SIGINT);
	sigaddset(&s_sigaction.sa_mask, SIGQUIT);
	s_sigaction.sa_handler = signal_handler;
	sigaction(SIGINT, &s_sigaction, NULL);
	s_sigaction.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s_sigaction, NULL);
}

void	signal_handler_exec(int signum)
{
	g_signal_received = signum;
}

void	handle_signal_child(void)
{
	struct sigaction	s_sigaction;

	// g_signal_received = 0;
	s_sigaction.sa_handler = SIG_DFL;
	sigaction(SIGINT, &s_sigaction, NULL);
	sigaction(SIGQUIT, &s_sigaction, NULL);
	// s_sigaction.sa_flags = SA_RESTART; // mais pourquoi ??
	// sigemptyset(&s_sigaction.sa_mask);
	// sigaddset(&s_sigaction.sa_mask, SIGINT);
	// sigaddset(&s_sigaction.sa_mask, SIGQUIT);
	// s_sigaction.sa_handler = &signal_handler_exec;
	// sigaction(SIGINT, &s_sigaction, NULL);
	// sigaction(SIGQUIT, &s_sigaction, NULL);
}

void	handle_signal_wait(void)
{
	struct sigaction	s_sigaction;

	g_signal_received = 0;
	s_sigaction.sa_flags = SA_RESTART; // mais pourquoi ??
	sigemptyset(&s_sigaction.sa_mask);
	sigaddset(&s_sigaction.sa_mask, SIGINT);
	sigaddset(&s_sigaction.sa_mask, SIGQUIT);
	s_sigaction.sa_handler = &signal_handler_exec;
	sigaction(SIGINT, &s_sigaction, NULL);
	sigaction(SIGQUIT, &s_sigaction, NULL);
}

// void	handle_signal_heredoc(void)
// {
// 	struct sigaction	s_sigaction;

// 	g_signal_received = 0;
// 	s_sigaction.sa_flags = SA_RESTART; // mais pourquoi ??
// 	sigemptyset(&s_sigaction.sa_mask);
// 	sigaddset(&s_sigaction.sa_mask, SIGINT);
// 	sigaddset(&s_sigaction.sa_mask, SIGQUIT);
// 	s_sigaction.sa_handler = &heredoc_signal_handler;
// 	sigaction(SIGINT, &s_sigaction, NULL);
// 	s_sigaction.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &s_sigaction, NULL);}

int	return_global(void)
{
	return (g_signal_received);
}

void	init_global(void)
{
	g_signal_received = 0;
}
