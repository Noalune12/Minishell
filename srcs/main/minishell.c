#include "minishell.h"
#include "heredoc.h"
#include "wildcard.h"
#include "ast.h"
#include "signals.h"

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	int			ret;

	minishell_init(&minishell, ac, av, envp);
	// rl_event_hook = &event;
	minishell_main_loop(&minishell);
	ret = minishell.exit_status;
	cleanup_exit(&minishell);
	return (ret);
}
