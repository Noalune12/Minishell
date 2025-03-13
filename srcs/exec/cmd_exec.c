#include "minishell.h"

#include <sys/types.h>
#include <sys/stat.h>

static size_t	list_size(t_list *list)
{
	t_list	*temp;
	size_t	size;

	temp = list;
	size = 0;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

static void	free_tab(char **tab, int i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
}

static char	**list_to_tab(t_minishell *minishell)
{
	t_list	*temp;
	char	**tab;
	size_t	i;

	temp = minishell->envp;
	tab = (char **)malloc((list_size(temp) + 1) * sizeof(char *));
	if (!tab)
	{
		error_handling_exec(minishell, "Malloc failed");
		exit (1);
	}
	i = 0;
	while (temp)
	{
		tab[i] = ft_strdup(temp->content);
		if (!tab[i])
		{
			free_tab(tab, i);
			error_handling_exec(minishell, "Malloc failed");
			exit (1);
		}
		temp = temp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

static int	exec_cmd(t_ast *node, t_minishell *minishell)
{
	char	**env;

	if ((ft_strncmp(node->cmd->cmds[0], "./", 2) == 0 || ft_strncmp(node->cmd->cmds[0], "/", 1) == 0)&& access(node->cmd->cmds[0], F_OK) == 0 && access(node->cmd->cmds[0], X_OK) != 0)
	{
		{
			ft_dprintf(STDERR_FILENO, "minishell: %s: ", node->cmd->cmds[0]);
			perror("");
			error_handling_exec(minishell, NULL);
			exit (126);
		}
	}
	env = list_to_tab(minishell);
	if (access(node->cmd->cmds[0], X_OK) == 0)
	{
		node->cmd->path = ft_strdup(node->cmd->cmds[0]);
		if (!(node->cmd->path))
		{
			error_handling_exec(minishell, "Malloc failed");
			exit (1);
		}
		if (execve(node->cmd->path, node->cmd->cmds, env) == -1)
			node->cmd->path = find_exec_cmd(node->cmd->cmds, minishell);
	}
	else
		node->cmd->path = find_exec_cmd(node->cmd->cmds, minishell);
	if (execve(node->cmd->path, node->cmd->cmds, env) == -1)
	{
		free_tab(env, list_size(minishell->envp));
		error_handling_exec(minishell, "execve failed");
		exit (1);
	}
	return (1);
}

int	handle_cmd(t_ast *node, t_minishell *minishell)
{
	int	ret;
	struct stat	path;

	ret = 0;
	if (!node->cmd->cmds[0][0]) //TODO find a better solution
	{
		ft_dprintf(STDERR_FILENO, CMD_NOT_FOUND, "");
		return (127);
	}
	if (stat(node->cmd->cmds[0], &path) == 0)
	{
		if (path.st_mode && (ft_strncmp(node->cmd->cmds[0], "./", 2) == 0 || ft_strncmp(node->cmd->cmds[0], "/", 1) == 0) && S_ISDIR(path.st_mode)) //TODO close fds
		{
			ft_dprintf(STDERR_FILENO, "minishell: %s: Is a directory\n", node->cmd->cmds[0]);
			return (126);
		}
		if (path.st_mode && (ft_strncmp(node->cmd->cmds[0], "./", 2) == 0 || ft_strncmp(node->cmd->cmds[0], "/", 1) == 0) && !S_ISREG(path.st_mode)) //TODO close fds
		{
			ft_dprintf(STDERR_FILENO, "minishell: %s: ", node->cmd->cmds[0]);
			perror("");
			return (127);
		}
	}
	handle_signal_child();
	minishell->pid = fork();
	if (minishell->pid == -1) //TODO close fds
			return (error_handling_exec(NULL, "fork failed"));
	if (minishell->pid == 0)
	{
		if (minishell->fd_in)
		{
			dup2(minishell->fd_in, STDIN_FILENO);
			close(minishell->fd_in); //TODO protect
		}
		if (minishell->fd_out)
		{
			dup2(minishell->fd_out, STDOUT_FILENO); //TODO protect
			close(minishell->fd_out); //TODO protect
		}
		exec_cmd(node, minishell);
	}
	waitpid(minishell->pid, &ret, 0);
	if (minishell->fd_in)
			close(minishell->fd_in); //TODO protect
	if (minishell->fd_out)
			close(minishell->fd_out); //TODO protect
	if (g_signal_received == SIGINT)
		ft_dprintf(STDOUT_FILENO, "\n");
	else if (g_signal_received == SIGQUIT)
		ft_dprintf(STDOUT_FILENO, "Quit (core dumped)\n");
	if (g_signal_received == 0 && WIFEXITED(ret))
	{
		g_signal_received = 0;
		return (WEXITSTATUS(ret));
	}
	else
		return (128 + g_signal_received);
	return (1);
}
