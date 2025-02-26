#include "minishell.h"

int	handle_redirout(t_ast *node, t_minishell *minishell)
{
	int	ret;

	minishell->pid = fork();
	if (minishell->pid == 0)
	{
		minishell->fd_out = open(node->cmd->cmds[0], O_WRONLY | O_CREAT | O_TRUNC, 0644); //protect
		if (minishell->fd_out == -1)
		{
			ft_dprintf(STDERR_FILENO, "bash: %s: Permission denied\n", node->cmd->cmds[0]);
			exit(1);
		}
		dup2(minishell->fd_out, STDOUT_FILENO); //protect
		close(minishell->fd_out);
		exec_minishell(node->left, minishell);
		exec_minishell(node->right, minishell);
		clear_token_list(minishell->token);
		free_env(minishell);
		free_ast(minishell->ast_node);
		exit(0); //needed if ls >out for instance to mark the end and redisplay prompt
	}
	waitpid(minishell->pid, &ret, 0);
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	return (1);
}
