#include "minishell.h"
#include "ast.h"
#include "exec.h"

int	handle_redirappend(t_ast *node, t_minishell *minishell)
{
	int	ret;
	int	fd;

	fd = open(node->cmd->cmds[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (minishell->fd_out == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: ", node->cmd->cmds[0]);
		perror("");
		return (1);
	}
	if (add_fd(&minishell->fds.fd_out, fd) == NULL)
	{
		close(fd);
		return (1);
	}
	ret = exec_minishell(node->left, minishell);
	delete_fd(&minishell->fds.fd_out, minishell->fds.fd_out.nb_elems - 1);
	close(fd);
	return (ret);
}
