#include "minishell.h"

static int	exec_left(t_ast *node, t_minishell *minishell)
{
	close(minishell->pipe_fd[0]);
	dup2(minishell->pipe_fd[1], STDOUT_FILENO); //protect
	close(minishell->pipe_fd[1]);
	exec_minishell(node->left, minishell);
	free_token_list(minishell->token);
	free_env(minishell);
	free_ast(minishell->ast_node);
	exit(0);
	return (0);
}

static int	exec_right(t_ast *node, t_minishell *minishell)
{
	int	ret;

	close(minishell->pipe_fd[1]);
	minishell->pid = fork(); //protect
	if (minishell->pid == 0)
	{
		dup2(minishell->pipe_fd[0], STDIN_FILENO); // protect
		close(minishell->pipe_fd[0]);
		ret = exec_minishell(node->right, minishell);
		free_token_list(minishell->token);
		free_env(minishell);
		free_ast(minishell->ast_node);
		exit(ret);
	}
	waitpid(minishell->pid, &ret, 0);
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	return (1);
}

int	handle_pipe(t_ast *node, t_minishell *minishell)
{
	int	ret;

	if (pipe(minishell->pipe_fd) == -1)
	{
		printf("Pipe error");
		return (1);
	}
	minishell->pid = fork(); // protect
	if (minishell->pid == 0)
		exec_left(node, minishell);
	else
		ret = exec_right(node, minishell);
	close(minishell->pipe_fd[1]);
	close(minishell->pipe_fd[0]);
	while (wait(NULL) != -1)
		;
	return (ret);
}
