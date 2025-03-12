#include "minishell.h"

int	handle_redirappend(t_ast *node, t_minishell *minishell)
{
	int	ret;

	if (minishell->fd_out)
		close(minishell->fd_out);
	minishell->fd_out = open(node->cmd->cmds[0], O_WRONLY | O_CREAT | O_APPEND, 0644); //protect
	if (minishell->fd_out == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: ", node->cmd->cmds[0]);
		perror("");
		return (1);
	}
	ret = exec_minishell(node->left, minishell);
	return (ret);
}
