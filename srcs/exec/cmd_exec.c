#include "minishell.h"

static int	exec_cmd(t_ast *node, t_minishell *minishell)
{
	if (access(node->cmd->cmds[0], X_OK) == 0)
		node->cmd->path = ft_strdup(node->cmd->cmds[0]);
	else
		node->cmd->path = find_exec_cmd(node->cmd->cmds, minishell, node);
	execve(node->cmd->path, node->cmd->cmds, NULL); // protect
	return (1);
}

int	handle_cmd(t_ast *node, t_minishell *minishell)
{
	minishell->pid = fork(); // protect
	if (minishell->pid == 0)
		exec_cmd(node, minishell);
	else
	{
		waitpid(minishell->pid, &minishell->status, 0);
		minishell->exit_code = WEXITSTATUS(minishell->status);
	}
	return (minishell->exit_code);
}
