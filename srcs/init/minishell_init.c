#include "minishell.h"

void	tty_check(void)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))  // protection pour ./minishell | ./minishell par exemple
	{
		ft_dprintf(STDERR_FILENO, "minishell: not a tty\n");
		exit(EXIT_SUCCESS);
	}
}

void	init_options(t_minishell *minishell)
{
	minishell->options = malloc(sizeof(t_options));
	if (!minishell->options)
	{
		ft_dprintf(STDERR_FILENO, "Memory allocation error\n");
		exit(EXIT_FAILURE); // proper exit ?
	}
	minishell->options->display_ast = false;
	minishell->options->display_tokens = false;
}

void	minishell_init(t_minishell *minishell, int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	ft_memset(minishell, 0, sizeof(t_minishell));
	minishell->envp = env_init(envp);
	init_options(minishell);
}
