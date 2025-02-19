#include "minishell.h"

void free_node(t_list *node) //utils ?
{
	if (node)
	{
		free(node->content);
		free(node);
	}
}

void remove_node(t_list **head, const char *var)
{
	t_list *current = *head;
	t_list *prev = NULL;
	char	*content;

	content = ft_strjoin(var, "="); // protect ?
	while (current)
	{
		if (ft_strncmp(current->content, content, ft_strlen(content)) == 0)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free_node(current);
			free(content);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_unset(char **cmds, t_list **env)
{
	size_t		i;
	char	*var;

	i = 0;
	if (!cmds[++i])
		return ;
	while (cmds[i])
	{
		var = ft_strdup(cmds[i]);
		remove_node(env, var);
		free(var);
		i++;
	}
}
