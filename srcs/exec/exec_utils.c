#include "minishell.h"

int	error_handling_exec(t_minishell *minishell, char *message)
{
		free_list(minishell->envp);
		free_ast(minishell->ast_node);
		free_list(minishell->token);
		if (message)
			ft_dprintf(STDERR_FILENO, "%s\n", message);
		return (1);
}
