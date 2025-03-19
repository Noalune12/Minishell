#include "minishell.h"

static int	exec_left(t_ast *node, t_minishell *minishell, int pipe_fd[2])
{
	handle_signal_wait();
	close(pipe_fd[0]);
	add_fd(&minishell->fds.fd_out, pipe_fd[1]);
	exec_minishell(node->left, minishell);
	delete_fd(&minishell->fds.fd_out, minishell->fds.fd_out.nb_elems - 1);
	close(pipe_fd[1]);
	error_handling_exec(minishell, NULL); // TODO function free all minishell ?
	exit(0);
	return (0);
}

static int	exec_right(t_ast *node, t_minishell *minishell, int pipe_fd[2])
{
	int	ret;

	handle_signal_wait();
	close(pipe_fd[1]);
	minishell->pid = fork();
	if (minishell->pid == -1)
	{
		close(pipe_fd[0]);
		ft_dprintf(STDERR_FILENO, "fork failed\n");
		return (1); //TODO no need exit ??
	}
	if (minishell->pid == 0)
	{
		add_fd(&minishell->fds.fd_in, pipe_fd[0]);
		ret = exec_minishell(node->right, minishell);
		delete_fd(&minishell->fds.fd_in, minishell->fds.fd_in.nb_elems - 1);
		close(pipe_fd[0]);
		error_handling_exec(minishell, NULL); // TODO function free all minishell ?
		exit(ret);
	}
	close(pipe_fd[0]);
	waitpid(minishell->pid, &ret, 0);
	if (g_signal_received == 0 && WIFEXITED(ret))
	{
		g_signal_received = 0;
		return (WEXITSTATUS(ret));
	}
	else
		return (128 + g_signal_received);
	return (1);
}

int	handle_pipe(t_ast *node, t_minishell *minishell)
{
	int	ret;
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
			return (error_handling_exec(NULL, "pipe failed"));
	minishell->is_pipe = 1;
	handle_signal_wait();
	minishell->pid = fork();
	if (minishell->pid == -1)
	{
		error_handling_exec(minishell, "fork failed");
		exit (1);
	}
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
		ft_dprintf(STDOUT_FILENO, "Quit (core dumped)\n");
	return (ret);
}
