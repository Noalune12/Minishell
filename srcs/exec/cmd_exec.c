/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:31 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 09:21:33 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

#include "ast.h"
#include "exec.h"
#include "fd.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "minishell.h"
#include "signals.h"

static char	**list_to_tab(t_minishell *minishell)
{
	t_list	*temp;
	char	**tab;
	size_t	i;

	temp = minishell->envp;
	tab = malloc((ft_lstsize(temp) + 1) * sizeof(char *));
	if (tab == NULL)
		exit (error_handling_exec(minishell, NULL));
	i = 0;
	while (temp)
	{
		tab[i] = ft_strdup(temp->content);
		if (!tab[i])
		{
			free_tab(tab, i);
			exit (error_handling_exec(minishell, NULL));
		}
		temp = temp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

static int	check_permission(t_ast *node, t_minishell *minishell)
{
	if (start_as_file(node) == 1 && access(node->cmd->cmds[0], F_OK) == 0
		&& access(node->cmd->cmds[0], X_OK) != 0)
	{
		ft_dprintf(STDERR_FILENO, SIMPLE_ERR, node->cmd->cmds[0]);
		perror("");
		error_handling_exec(minishell, NULL);
		return (0);
	}
	return (1);
}

static int	exec_cmd(t_ast *node, t_minishell *minishell)
{
	char	**env;

	if (check_permission(node, minishell) == 0)
		exit (126);
	env = list_to_tab(minishell);
	if (access(node->cmd->cmds[0], X_OK) == 0)
	{
		node->cmd->path = ft_strdup(node->cmd->cmds[0]);
		if (node->cmd->path == NULL)
			exit(error_handling_exec(minishell, NULL));
		if (execve(node->cmd->path, node->cmd->cmds, env) == -1)
			node->cmd->path = find_exec_cmd(node->cmd->cmds, minishell, env);
	}
	else
		node->cmd->path = find_exec_cmd(node->cmd->cmds, minishell, env);
	close_and_free_fds(&minishell->fds.fd_in);
	close_and_free_fds(&minishell->fds.fd_out);
	if (execve(node->cmd->path, node->cmd->cmds, env) == -1)
	{
		free_tab(env, ft_lstsize(minishell->envp));
		exit(error_handling_exec(minishell, EXECVE_ERR));
	}
	return (1);
}

static int	exec_in_child(t_ast *node, t_minishell *minishell, int *ret)
{
	minishell->pid = fork();
	if (minishell->pid == -1)
		return (error_handling_exec(NULL, FORK_ERR));
	if (minishell->pid == 0)
	{
		handle_signal_child();
		if (dup_fd(&minishell->fds.fd_in, STDIN_FILENO) == 0)
			exit (error_handling_exec(minishell, DUP2_ERR));
		if (dup_fd(&minishell->fds.fd_out, STDOUT_FILENO) == 0)
			exit (error_handling_exec(minishell, DUP2_ERR));
		close_fd(&minishell->fds.fd_in);
		close_fd(&minishell->fds.fd_out);
		exec_cmd(node, minishell);
	}
	if (waitpid(minishell->pid, ret, 0) == -1)
		return (error_handling_exec(NULL, WAIT_ERR));
	return (0);
}

int	handle_cmd(t_ast *node, t_minishell *minishell)
{
	int	ret;
	int	child_ret;

	ret = check_cmd(node);
	if (ret != 0)
		return (ret);
	if (ft_strcmp(node->cmd->cmds[0], minishell->exec) == 0)
		minishell->is_pipe = 1;
	handle_signal_wait();
	child_ret = exec_in_child(node, minishell, &ret);
	if (child_ret == 1)
		return (1);
	if (minishell->is_pipe == 0 && g_signal_received == SIGINT)
		ft_dprintf(STDOUT_FILENO, "\n");
	else if (minishell->is_pipe == 0 && g_signal_received == SIGQUIT)
		ft_dprintf(STDOUT_FILENO, SIGQUIT_MESSAGE);
	minishell->is_pipe = 0;
	if (WIFEXITED(ret))
	{
		g_signal_received = 0;
		return (WEXITSTATUS(ret));
	}
	else if (__WIFSIGNALED(ret))
		return (128 + g_signal_received);
	return (1);
}
