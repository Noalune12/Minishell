#include "minishell.h"

//list to tab

int	exec_cmd(t_ast *node, t_minishell *minishell)
{
	// char *path;
	// path = ft_strjoin("/usr/bin/", node->cmd->cmds[0]);
	if (access(node->cmd->cmds[0], X_OK) == 0)
		node->cmd->path = ft_strdup(node->cmd->cmds[0]);
	else
		node->cmd->path = find_exec_cmd(node->cmd->cmds, minishell, node);
	execve(node->cmd->path, node->cmd->cmds, NULL); // protect
	// execve(path, node->cmd->cmds, NULL); // protect
	return (1);
}

int	update_exit_code(int exit_code, t_minishell *minishell, t_ast *node)
{
	static int result;

	if (node->last_branch == 1)
	{
		result = exit_code;
	}
	printf("result = %d\n", result);
	minishell->exit_status = result;
	printf("exit status = %d\n", minishell->exit_status);
	return (0);
}

int	exec_minishell(t_ast *node, t_exec *exec, t_minishell *minishell)
{
	int		fd_in;
	int		fd_out;
	// int		status;

	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
	{
		minishell->pid = fork(); // protect
		if (minishell->pid == 0)
			exec_cmd(node, minishell);
		// else
		// 	waitpid(minishell->pid, 0, 0);
	}
	else if (node->type == NODE_PIPE)
	{
		if (pipe(exec->pipe_fd) == -1)
		{
			printf("Pipe error");
			return (1);
		}
		minishell->pid = fork();
		if (minishell->pid == 0)
		{
			close(exec->pipe_fd[0]);
			dup2(exec->pipe_fd[1], STDOUT_FILENO); //protect
			close(exec->pipe_fd[1]);
			exec_minishell(node->left, exec, minishell);
			exit(0);
		}
		else
		{
			minishell->pid = fork();
			if (minishell->pid == 0)
			{
				close(exec->pipe_fd[1]);
				dup2(exec->pipe_fd[0], STDIN_FILENO); // protect
				close(exec->pipe_fd[0]);
				exec_minishell(node->right, exec, minishell);
				exit(0);
			}
		}
		close(exec->pipe_fd[1]);
		close(exec->pipe_fd[0]);
	}
	else if (node->type == NODE_REDIR_IN)
	{
		minishell->pid = fork();
		if (minishell->pid == 0)
		{
			fd_in = open(node->cmd->cmds[0], O_RDONLY); //protect
			if (fd_in == -1)
			{
				printf("bash: %s: No such file or directory\n", node->cmd->cmds[0]);
				exit(1);
			}
			dup2(fd_in, STDIN_FILENO); //protect
			close(fd_in);
			exec_minishell(node->left, exec, minishell);
			exec_minishell(node->right, exec, minishell);
			exit(0); //needed if <Makefile cat for instance to not display the prompt in cat
		}
		// else
		// 	waitpid(minishell->pid, 0, 0);
	}
	else if (node->type == NODE_REDIR_OUT)
	{
		minishell->pid = fork();
		if (minishell->pid == 0)
		{
			fd_out = open(node->cmd->cmds[0], O_WRONLY | O_CREAT | O_TRUNC, 0644); //protect
			if (fd_out == -1)
			{
				printf("bash: %s: Permission denied\n", node->cmd->cmds[0]);
				exit(1);
			}
			dup2(fd_out, STDOUT_FILENO); //protect
			close(fd_out);
			exec_minishell(node->left, exec, minishell);
			exec_minishell(node->right, exec, minishell);
			exit(0); //needed if ls >out for instance to mark the end and redisplay prompt
		}
		// else
		// 	waitpid(minishell->pid, 0, 0);
	}
	else if (node->type == NODE_APPEND)
	{
		minishell->pid = fork();
		if (minishell->pid == 0)
		{
			fd_out = open(node->cmd->cmds[0], O_WRONLY | O_CREAT | O_APPEND, 0644); //protect
			if (fd_out == -1)
			{
				printf("bash: %s: Permission denied\n", node->cmd->cmds[0]);
				exit(1);
			}
			dup2(fd_out, STDOUT_FILENO); //protect
			close(fd_out);
			exec_minishell(node->left, exec, minishell);
			exec_minishell(node->right, exec, minishell);
			exit(0);
		}
		// else
		// 	waitpid(minishell->pid, 0, 0);
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
	// 	exec_minishell(node->left, exec, minishell);
	// 	exec_minishell(node->right, exec, minishell);
	// }

	// int exit_code;
	waitpid(minishell->pid, &minishell->status, 0);
	if (node->last_branch == 1)
		minishell->exit_code = WEXITSTATUS(minishell->status);
	printf("Le code de sortie de %s est : %d\n", node->cmd->cmds[0], minishell->exit_code);
	if (node->last_branch == 1)
		return (update_exit_code(minishell->exit_code, minishell, node));
	else
		return (0);
}
