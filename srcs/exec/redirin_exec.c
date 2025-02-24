#include "minishell.h"

int	handle_redirin(t_ast *node, t_minishell *minishell)
{
	int	ret;

	minishell->pid = fork();
	if (minishell->pid == 0)
	{
		minishell->fd_in = open(node->cmd->cmds[0], O_RDONLY); //protect
		if (minishell->fd_in == -1)
		{
			ft_dprintf(STDERR_FILENO, "bash: %s: No such file or directory\n", node->cmd->cmds[0]);
			exit (1);
		}
		dup2(minishell->fd_in, STDIN_FILENO); //protect
		close(minishell->fd_in);
		exec_minishell(node->left, minishell);
		exec_minishell(node->right, minishell);
		clear_token_list(minishell->token);
		free_env(minishell);
		free_ast(minishell->ast_node);
		exit(0); //needed if <Makefile cat for instance to not display the prompt in cat
	}
	waitpid(minishell->pid, &ret, 0);
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	return (1);
}
