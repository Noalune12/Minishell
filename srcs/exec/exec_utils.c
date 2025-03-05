#include "minishell.h"

int	error_handling_exec(t_minishell *minishell, char *message)
{
		free_list(minishell->envp);
		free_ast(minishell->ast_node);
		free_list(minishell->token);
		if (minishell->fd_in)
			close(minishell->fd_in); //TODO protect
		if (minishell->fd_out)
			close(minishell->fd_out); //TODO protect
		if (message)
			ft_dprintf(STDERR_FILENO, "%s\n", message);
		return (1);
}
