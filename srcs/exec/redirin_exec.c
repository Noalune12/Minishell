#include "minishell.h"

int	handle_redirin(t_ast *node, t_minishell *minishell)
{
	int	ret;
	int	fd;

	// if (minishell->fd_in)
	// 	close(minishell->fd_in);
	fd = open(node->cmd->cmds[0], O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: ", node->cmd->cmds[0]);
		perror("");
		return (1);
	}
	add_fd(&minishell->fds.fd_in, fd);
	ret = exec_minishell(node->left, minishell);
	delete_fd(&minishell->fds.fd_in, minishell->fds.fd_in.nb_elems - 1);
	close(fd);
	return (ret);
}
