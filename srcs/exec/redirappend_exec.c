#include "minishell.h"

static void	open_dup_append(t_ast *node, t_minishell *minishell)
{
	minishell->fd_out = open(node->cmd->cmds[0], O_WRONLY | O_CREAT | O_APPEND, 0644); //protect
	if (minishell->fd_out == -1)
	{
		ft_dprintf(STDERR_FILENO, "bash: %s: Permission denied\n", node->cmd->cmds[0]);
		error_handling_exec(minishell, NULL);
		exit(1);
	}
	if (dup2(minishell->fd_out, STDOUT_FILENO) == -1)
	{
		close(minishell->fd_out); //TODO protect
		error_handling_exec(minishell, "dup2 failed");
		exit(1);
	}
}

int	handle_redirappend(t_ast *node, t_minishell *minishell)
{
	int	ret;

	minishell->pid = fork();
	if (minishell->pid == 0)
	{
		open_dup_append(node, minishell);
		close(minishell->fd_out); //TODO protect
		exec_minishell(node->left, minishell);
		exec_minishell(node->right, minishell);
		error_handling_exec(minishell, NULL); // TODO function free all minishell ?
		exit(0);
	}
	waitpid(minishell->pid, &ret, 0);
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	return (1);
}
