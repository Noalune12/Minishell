#include "minishell.h"

static int	exec_left(t_ast *node, t_minishell *minishell)
{
	close(minishell->pipe_fd[0]);  //TODO protect
	// if (dup2(minishell->pipe_fd[1], STDOUT_FILENO) == -1) // add to fd_out
	// {
	// 	close(minishell->pipe_fd[1]);  //TODO protect
	// 	error_handling_exec(minishell, "dup2 failed");
	// 	exit(1);
	// }
	// close(minishell->pipe_fd[1]);  //TODO protect
	// if (minishell->fd_out) // TODO check for redirout
	// 	close (minishell->fd_out);
	add_fd(&minishell->fds.fd_out, minishell->pipe_fd[1]);
	exec_minishell(node->left, minishell);
	delete_fd(&minishell->fds.fd_out, minishell->fds.fd_out.nb_elems - 1);
	close(minishell->pipe_fd[1]);
	close_and_free_fds(&minishell->fds.fd_in);
	close_and_free_fds(&minishell->fds.fd_out);
	error_handling_exec(minishell, NULL); // TODO function free all minishell ?
	exit(0);
	return (0);
}

static int	exec_right(t_ast *node, t_minishell *minishell)
{
	int	ret;

	close(minishell->pipe_fd[1]); //TODO protect
	minishell->pid = fork();
	if (minishell->pid == -1)
	{
		close(minishell->pipe_fd[0]);  //TODO protect
		ft_dprintf(STDERR_FILENO, "fork failed\n");
		return (1); //TODO no need exit ??
	}
	if (minishell->pid == 0)
	{
		// if (dup2(minishell->pipe_fd[0], STDIN_FILENO) == -1)// add to fd_in
		// {
		// 	close(minishell->pipe_fd[0]);  //TODO protect
		// 	error_handling_exec(minishell, "dup2 failed");
		// 	exit(1);
		// }
		// close(minishell->pipe_fd[0]);  //TODO protect
		// if (minishell->fd_in) // TODO check for redirout
		// 	close (minishell->fd_in);
		add_fd(&minishell->fds.fd_in, minishell->pipe_fd[0]);
		ret = exec_minishell(node->right, minishell);
		delete_fd(&minishell->fds.fd_in, minishell->fds.fd_in.nb_elems - 1);
		close(minishell->pipe_fd[0]);
		close_and_free_fds(&minishell->fds.fd_in);
		close_and_free_fds(&minishell->fds.fd_out);
		error_handling_exec(minishell, NULL); // TODO function free all minishell ?
		exit(ret);
	}
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

	if (pipe(minishell->pipe_fd) == -1)
			return (error_handling_exec(NULL, "pipe failed"));
	handle_signal_child();
	minishell->pid = fork();
	if (minishell->pid == -1)
	{
		error_handling_exec(minishell, "fork failed");
		exit (1); // TODO add variable to know if we are in parent or child before and exit if in a child
	}
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
