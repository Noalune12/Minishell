/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:22:01 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 09:22:02 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>

#include "ast.h"
#include "exec.h"
#include "ft_dprintf.h"
#include "minishell.h"
#include "signals.h"

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

static void	close_fds(int pipe_fd[2])
{
	close(pipe_fd[1]);
	close(pipe_fd[0]);
}

int	handle_pipe(t_ast *node, t_minishell *minishell)
{
	int	ret;
	int	pipe_fd[2];
	int	was_pipe;

	if (pipe(pipe_fd) == -1)
		return (error_handling_exec(NULL, PIPE_ERR));
	was_pipe = minishell->is_pipe;
	minishell->is_pipe = 1;
	handle_signal_wait();
	minishell->pid = fork();
	if (minishell->pid == -1)
		return (error_handling_pipe(pipe_fd, FORK_ERR));
	if (minishell->pid == 0)
		exec_left(node, minishell, pipe_fd);
	else
		ret = exec_right(node, minishell, pipe_fd);
	close_fds(pipe_fd);
	while (wait(NULL) != -1)
		;
	minishell->is_pipe = was_pipe;
	if (!was_pipe && g_signal_received == SIGINT)
		ft_dprintf(STDOUT_FILENO, "\n");
	else if (!was_pipe && g_signal_received == SIGQUIT)
		ft_dprintf(STDOUT_FILENO, SIGQUIT_MESSAGE);
	return (ret);
}
