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

static char	**list_to_tab(t_minishell *minishell)
{
	t_list	*temp;
	char	**tab;
	size_t	i;

	temp = minishell->envp;
	tab = (char **)malloc((list_size(temp) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (temp)
	{
		tab[i] = ft_strdup(temp->content);
		if (!tab[i])
		{
			while (i > 0)
				free(tab[--i]);
			free(tab);
			return (NULL);
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
		node->cmd->path = ft_strdup(node->cmd->cmds[0]);
	else
		node->cmd->path = find_exec_cmd(node->cmd->cmds, minishell, node);
	env = list_to_tab(minishell);
	if (!env)
	{
		ft_dprintf(STDERR_FILENO, "Malloc failed\n");
		// free and exit ??
	}
	execve(node->cmd->path, node->cmd->cmds, env); // protect
	return (1);
}

int	handle_cmd(t_ast *node, t_minishell *minishell)
{
	int	ret;

	minishell->pid = fork(); // protect
	if (minishell->pid == 0)
		exec_cmd(node, minishell);
	waitpid(minishell->pid, &ret, 0);
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	return (1);
}
