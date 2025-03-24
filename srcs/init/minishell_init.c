#include "minishell.h"
#include "env.h"

void	tty_check(void)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		ft_dprintf(STDERR_FILENO, "minishell: not a tty\n");
		exit(EXIT_FAILURE); // exit_failure ??
	}
}

static void	init_options(t_minishell *minishell)
{
	minishell->options = malloc(sizeof(t_options));
	if (!minishell->options)
	{
		free_list(minishell->envp);
		ft_dprintf(STDERR_FILENO, "Memory allocation error\n");
		exit(EXIT_FAILURE); // proper exit ?
	}
	minishell->options->display_ast = false;
	minishell->options->display_tokens = false;
}

static bool init_fd_info(t_fd_info *fd)
{
	fd->fds = malloc(sizeof(int) * 10);
	if (!fd->fds)
		return (0);
	fd->nb_elems = 0;
	fd->capacity = 10;
	return (1);
}

void	minishell_init(t_minishell *minishell, int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	// tty_check();
	ft_memset(minishell, 0, sizeof(t_minishell));
	minishell->exec = av[0];
	minishell->envp = env_init(envp); // TODO finish protection for minimal env
	if (minishell->envp == NULL)
		exit(EXIT_FAILURE);
	minishell->pid = -1;
	init_options(minishell);
	if (init_fd_info(&minishell->fds.fd_in) == 0
		|| init_fd_info(&minishell->fds.fd_out) == 0)
	{
		cleanup_shell(minishell);
		ft_dprintf(STDERR_FILENO, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
}
