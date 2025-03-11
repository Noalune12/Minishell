#include "minishell.h"

// TODO expand

int	handle_heredocin(t_ast *node, t_minishell *minishell)
{
	int	ret;

	if (minishell->fd_in)
		close(minishell->fd_in);
	minishell->fd_in = open(node->cmd->cmds[0], O_RDONLY);
	if (minishell->fd_in == -1)
	{
		ft_dprintf(STDERR_FILENO, ERROR_INFILE, node->cmd->cmds[0]);
		// error_handling_exec(minishell, NULL);
		return (1);
	}
	ret = exec_minishell(node->left, minishell);
	unlink(node->cmd->cmds[0]);
	return (ret);
}
