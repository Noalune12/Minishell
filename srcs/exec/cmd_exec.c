#include "minishell.h"

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

	if (access(node->cmd->cmds[0], X_OK) == 0)
	{
		node->cmd->path = ft_strdup(node->cmd->cmds[0]);
		if (!(node->cmd->path))
		{
			error_handling_exec(minishell, "Malloc failed");
			exit (1);
		}
	}
	else
		node->cmd->path = find_exec_cmd(node->cmd->cmds, minishell);
	env = list_to_tab(minishell);
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

	// signal(SIGINT, signal_handler_exec);
	minishell->pid = fork();
	if (minishell->pid == -1)
	{
		error_handling_exec(minishell, "fork failed");
		exit (1); // TODO add variable to know if we are in parent or child before and exit if in a child
	}
	if (minishell->pid == 0)
		exec_cmd(node, minishell);
	waitpid(minishell->pid, &ret, 0);
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	return (1);
}
