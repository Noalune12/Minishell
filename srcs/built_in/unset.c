#include "minishell.h"

static void	free_node(t_list *node) //TODO utils ?
{
	if (node)
	{
		free(node->content);
		free(node);
	}
}

static int	compare_remove_node(t_list **head, char *content,
	t_list *current, t_list *prev)
{
	if (ft_strncmp(current->content, content, ft_strlen(content)) == 0)
	{
		if (prev == NULL)
			*head = current->next;
		else
			prev->next = current->next;
		free_node(current);
		free(content);
		return (0);
	}
	else
		return (1);
}

int	remove_node(t_list **head, char *var)
{
	t_list	*current;
	t_list	*prev;
	char	*content;

	current = *head;
	prev = NULL;
	content = ft_strjoin(var, "=");
	if (!content)
	{
		ft_dprintf(STDERR_FILENO, "Malloc failed\n");
		return (1);
	}
	while (current)
	{
		if (compare_remove_node(head, content, current, prev) == 0)
			return (0);
		prev = current;
		current = current->next;
	}
	free(content);
	return (0);
}

int	ft_unset(char **cmds, t_minishell *minishell)
{
	size_t	i;
	char	*var;
	int		ret;

	i = 0;
	ret = 0;
	if (!cmds[++i])
		return (ret);
	while (cmds[i])
	{
		var = ft_strdup(cmds[i]);
		if (!var)
		{
			ft_dprintf(STDERR_FILENO, "Malloc failed\n");
			ret = 1;
		}
		if (remove_node(&minishell->envp, var) == 1)
			ret = 1;
		free(var);
		i++;
	}
	return (ret);
}
