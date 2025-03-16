#include "minishell.h"

// static void	open_dup_infile(t_ast *node, t_minishell *minishell)
// {
// 	minishell->fd_in = open(node->cmd->cmds[0], O_RDONLY);
// 	if (minishell->fd_in == -1)
// 	{
// 		ft_dprintf(STDERR_FILENO, ERROR_INFILE, node->cmd->cmds[0]);
// 		error_handling_exec(minishell, NULL);
// 		exit (1);
// 	}
// 	if (dup2(minishell->fd_in, STDIN_FILENO) == -1)
// 	{
// 		close(minishell->fd_in); //TODO protect
// 		error_handling_exec(minishell, "dup2 failed");
// 		exit(1);
// 	}
// }

int	handle_redirin(t_ast *node, t_minishell *minishell)
{
	int	ret;

	// if (minishell->fd_in)
	// 	close(minishell->fd_in);
	minishell->fd_in = open(node->cmd->cmds[0], O_RDONLY);
	if (minishell->fd_in == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: ", node->cmd->cmds[0]);
		perror("");
		return (1);
	}
	ret = exec_minishell(node->left, minishell);
	close(minishell->fd_in);
	return (ret);
}
