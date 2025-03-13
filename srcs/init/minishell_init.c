#include "minishell.h"

void	tty_check(void)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))  // protection pour ./minishell | ./minishell par exemple
	{
		ft_dprintf(STDERR_FILENO, "minishell: not a tty\n");
		exit(EXIT_SUCCESS);
	}
}

void	minishell_init(t_minishell *minishell, int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	ft_memset(minishell, 0, sizeof(t_minishell));
	minishell->envp = env_init(envp);
	minishell->pid = -1;
}
