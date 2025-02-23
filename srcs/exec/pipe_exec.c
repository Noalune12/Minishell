#include "minishell.h"

int	handle_pipe(t_ast *node, t_minishell *minishell)
{
	if (pipe(minishell->pipe_fd) == -1)
	{
		printf("Pipe error");
		return (1);
	}
	minishell->pid = fork();
	if (minishell->pid == 0)
	{
		close(minishell->pipe_fd[0]);
		dup2(minishell->pipe_fd[1], STDOUT_FILENO); //protect
		close(minishell->pipe_fd[1]);
		minishell->exit_status = exec_minishell(node->left, minishell);
		clear_token_list(minishell->token);
		free_env(minishell);
		free_ast(minishell->ast_node);
		exit(minishell->exit_status);
	}
	else
	{
		minishell->pid = fork();
		if (minishell->pid == 0)
		{
			close(minishell->pipe_fd[1]);
			dup2(minishell->pipe_fd[0], STDIN_FILENO); // protect
			close(minishell->pipe_fd[0]);
			minishell->exit_status = exec_minishell(node->right, minishell);
			clear_token_list(minishell->token);
			free_env(minishell);
			free_ast(minishell->ast_node);
			exit(minishell->exit_status);
		}
	}
	close(minishell->pipe_fd[1]);
	close(minishell->pipe_fd[0]);
	wait(NULL);
	wait(NULL);
	return (0);
}
