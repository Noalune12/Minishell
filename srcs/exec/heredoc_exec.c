#include "minishell.h"

// TODO expand

static void	open_dup_heredoc(t_ast *node, t_minishell *minishell)
{
	minishell->fd_in = open(node->cmd->cmds[0], O_RDONLY);
	if (minishell->fd_in == -1)
	{
		ft_dprintf(STDERR_FILENO, ERROR_INFILE, node->cmd->cmds[0]);
		error_handling_exec(minishell, NULL);
		exit (1);
	}
	if (dup2(minishell->fd_in, STDIN_FILENO) == -1)
	{
		close(minishell->fd_in); //TODO protect
		error_handling_exec(minishell, "dup2 failed");
		exit(1);
	}
}

int	handle_heredocin(t_ast *node, t_minishell *minishell)
{
	int	ret;

	minishell->pid = fork();
	if (minishell->pid == 0)
	{
		open_dup_heredoc(node, minishell);
		close(minishell->fd_in); //TODO protect
		exec_minishell(node->left, minishell);
		exec_minishell(node->right, minishell);
		error_handling_exec(minishell, NULL); // TODO function free all minishell ?
		exit(0); //needed if <Makefile cat for instance to not display the prompt in cat
	}
	waitpid(minishell->pid, &ret, 0);
	unlink(node->cmd->cmds[0]);
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	return (1);
}
