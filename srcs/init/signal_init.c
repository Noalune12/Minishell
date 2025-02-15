#include "minishell.h"

int	g_global_variable;

void	signal_handler(int signum) //ctrl c
{
	if (signum == SIGINT)
	{
		g_global_variable = SIGINT;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
		g_global_variable = SIGQUIT;
}
