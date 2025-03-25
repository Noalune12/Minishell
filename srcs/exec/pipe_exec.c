#include "minishell.h"
#include "ast.h"
#include "exec.h"

static int	exec_left(t_ast *node, t_minishell *minishell, int pipe_fd[2])
{
	close(pipe_fd[0]);
	if (add_fd(&minishell->fds.fd_out, pipe_fd[1]) == NULL)
	{
		close(pipe_fd[1]);
		exit(error_handling_exec(minishell, NULL));
	}
	exec_minishell(node->left, minishell);
	close(pipe_fd[1]);
	error_handling_exec(minishell, NULL);
	exit(0);
}

static int	exec_right(t_ast *node, t_minishell *minishell, int pipe_fd[2])
{
	int	ret;

	close(pipe_fd[1]);
	minishell->pid = fork();
	if (minishell->pid == -1)
		return (error_handling_exec(NULL, FORK_ERR));
	if (minishell->pid == 0)
	{
		if (add_fd(&minishell->fds.fd_in, pipe_fd[0]) == NULL)
		{
			close(pipe_fd[0]);
			exit(error_handling_exec(minishell, NULL));
		}
		ret = exec_minishell(node->right, minishell);
		close(pipe_fd[0]);
		error_handling_exec(minishell, NULL);
		exit(ret);
	}
	if (waitpid(minishell->pid, &ret, 0) == -1)
		return (error_handling_exec(NULL, WAIT_ERR));
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	return (1);
}

static int	error_handling_pipe(int pipe_fd[2], char *message)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (message)
		ft_dprintf(STDERR_FILENO, "%s\n", message);
	return (1);
}

int	handle_pipe(t_ast *node, t_minishell *minishell)
{
	int	ret;
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (error_handling_exec(NULL, PIPE_ERR));
	minishell->is_pipe = 1;
	handle_signal_wait();
	minishell->pid = fork();
	if (minishell->pid == -1)
		return (error_handling_pipe(pipe_fd, FORK_ERR));
	if (minishell->pid == 0)
		exec_left(node, minishell, pipe_fd);
	else
		ret = exec_right(node, minishell, pipe_fd);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	while (wait(NULL) != -1)
		;
	minishell->is_pipe = 0;
	if (g_signal_received == SIGINT)
		ft_dprintf(STDOUT_FILENO, "\n");
	else if (g_signal_received == SIGQUIT)
		ft_dprintf(STDOUT_FILENO, SIGQUIT_MESSAGE);
	return (ret);
}
