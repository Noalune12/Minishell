#include "minishell.h"

int	handle_redirappend(t_ast *node, t_minishell *minishell)
{
	minishell->pid = fork();
	if (minishell->pid == 0)
	{
		minishell->fd_out = open(node->cmd->cmds[0], O_WRONLY | O_CREAT | O_APPEND, 0644); //protect
		if (minishell->fd_out == -1)
		{
			printf("bash: %s: Permission denied\n", node->cmd->cmds[0]);
			exit(1);
		}
		dup2(minishell->fd_out, STDOUT_FILENO); //protect
		close(minishell->fd_out);
		exec_minishell(node->left, minishell);
		exec_minishell(node->right, minishell);
		clear_token_list(minishell->token);
		free_env(minishell);
		free_ast(minishell->ast_node);
		exit(0);
	}
	else
		waitpid(minishell->pid, 0, 0);
	return (0);
}
