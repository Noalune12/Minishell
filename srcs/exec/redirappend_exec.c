#include "minishell.h"

int	handle_redirappend(t_ast *node, t_minishell *minishell)
{
	int	ret;
	int	fd;

	// if (minishell->fd_out)
	// 	close(minishell->fd_out);
	fd = open(node->cmd->cmds[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (minishell->fd_out == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: ", node->cmd->cmds[0]);
		perror("");
		// error_handling_exec(minishell, NULL);
		return (1);
	}
	add_fd(&minishell->fds.fd_out, fd);
	ret = exec_minishell(node->left, minishell);
	delete_fd(&minishell->fds.fd_out, minishell->fds.fd_out.nb_elems - 1);
	close(fd);
	return (ret);
}
