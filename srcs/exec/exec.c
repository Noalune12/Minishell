#include "minishell.h"

//list to tab

int	exec_cmd(t_ast *node, t_list *envp)
{
	// char *path;
	// path = ft_strjoin("/usr/bin/", node->cmd->cmds[0]);
	if (access(node->cmd->cmds[0], X_OK) == 0)
		node->cmd->path = ft_strdup(node->cmd->cmds[0]);
	else
		node->cmd->path = find_exec_cmd(node->cmd->cmds, envp);
	execve(node->cmd->path, node->cmd->cmds, NULL); // protect
	// execve(path, node->cmd->cmds, NULL); // protect
	return (1);
}

int	exec_minishell(t_ast *node, t_exec *exec, t_minishell *minishell)
{
	pid_t	pid = 0;
	pid_t	pid_left = 0;
	pid_t	pid_right = 0;
	int		fd_in;
	int		fd_out;

	if (!node)
		return (-1);

	if (node->type == NODE_COMMAND)
	{
		pid = fork(); // protect
		if (pid == 0)
		{
			exec_cmd(node, minishell->envp);
			exit(0);
		}
		// else
		// 	waitpid(pid, 0, 0);
	}
	else if (node->type == NODE_PIPE)
	{
		if (pipe(exec->pipe_fd) == -1)
		{
			printf("Pipe error");
			return (1);
		}
		pid_left = fork();
		if (pid_left == 0)
		{
			close(exec->pipe_fd[0]);
			dup2(exec->pipe_fd[1], STDOUT_FILENO); //protect
			close(exec->pipe_fd[1]);
			exec_minishell(node->left, exec, minishell);
			exit(0);
		}
		else
		{
			pid_right = fork();
			if (pid_right == 0)
			{
				close(exec->pipe_fd[1]);
				dup2(exec->pipe_fd[0], STDIN_FILENO); // protect
				close(exec->pipe_fd[0]);
				exec_minishell(node->right, exec, minishell);
				exit(0);
			}
		}
		// waitpid(pid_left, 0, 0);
		// waitpid(pid_right, 0, 0);
		close(exec->pipe_fd[1]);
		close(exec->pipe_fd[0]);
	}
	else if (node->type == NODE_REDIR_IN)
	{
		pid = fork();
		if (pid == 0)
		{
			fd_in = open(node->cmd->cmds[0], O_RDONLY); //protect
			dup2(fd_in, STDIN_FILENO); //protect
			close(fd_in);
			exec_minishell(node->left, exec, minishell);
			exec_minishell(node->right, exec, minishell);
			exit(0); //needed if <Makefile cat for instance to not display the prompt in cat
		}
		// else
		// 	waitpid(pid, 0, 0);
	}
	else if (node->type == NODE_REDIR_OUT)
	{
		pid = fork();
		if (pid == 0)
		{
			fd_out = open(node->cmd->cmds[0], O_WRONLY | O_CREAT | O_TRUNC, 0644); //protect
			dup2(fd_out, STDOUT_FILENO); //protect
			close(fd_out);
			exec_minishell(node->left, exec, minishell);
			exec_minishell(node->right, exec, minishell);
			exit(0); //needed if ls >out for instance to mark the end and redisplay prompt
		}
		// else
		// 	waitpid(pid, 0, 0);
	}
	else if (node->type == NODE_APPEND)
	{
		pid = fork();
		if (pid == 0)
		{
			fd_out = open(node->cmd->cmds[0], O_WRONLY | O_CREAT | O_APPEND, 0644); //protect
			dup2(fd_out, STDOUT_FILENO); //protect
			close(fd_out);
			exec_minishell(node->left, exec, minishell);
			exec_minishell(node->right, exec, minishell);
			exit(0);
		}
		// else
		// 	waitpid(pid, 0, 0);
	}
	else if (node->type == NODE_BUILTIN)
	{
		ft_builtin(node, minishell);
		exec_minishell(node->left, exec, minishell);
		exec_minishell(node->right, exec, minishell);
	}
	// else if (node->type == NODE_AND)
	// {
	// 	if (pipe(exec->pipe_fd) == -1)
	// 	{
	// 		printf("Pipe error");
	// 		return (1);
	// 	}
	// 	exec_minishell(node->left, exec);
	// 	exec_minishell(node->right, exec);
	// }

	// heredoc
	// &&
	// ||
	waitpid(pid_left, 0, 0);
	waitpid(pid_right, 0, 0);
	waitpid(pid, 0, 0);
	// close(exec->pipe_fd[1]);
	// close(exec->pipe_fd[0]);
	return (0);
}
