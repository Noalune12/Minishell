#include "minishell.h"

// TODO expand

int	handle_heredocin(t_ast *node, t_minishell *minishell)
{
	int	ret;

	if (node->cmd->to_expand == true)
		// open and replace from env
	if (minishell->fd_in)
		close(minishell->fd_in);
	minishell->fd_in = open(node->cmd->cmds[0], O_RDONLY);
	if (minishell->fd_in == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: ", node->cmd->cmds[0]);
		perror("");
		return (1);
	}
	ret = exec_minishell(node->left, minishell);
	unlink(node->cmd->cmds[0]);
	return (ret);
}
