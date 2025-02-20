#include "../../../incs/minishell.h"

void free_node(t_list *node)
{
	if (node)
	{
		free(node->content);
		free(node);
	}
}

void remove_node(t_list **head, const char *var, int len)
{
	t_list *current = *head;
	t_list *prev = NULL;
	char	*content;

	content = ft_strjoin(var, "="); // protect ?
	while (current)
	{
		if (strncmp(current->content, content, len + 1) == 0)
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

void	ft_unset(char *input, t_list **env)
{
	int		i;
	int		len;
	char	*var;

	i = 5;
	len = 0;
	while (input[i] == ' ')
		i++;
	if (!input[i])
		return ;
	while (input[i])
	{
		if (input[i] == ' ')
		{
			var = ft_strndup(input + i - len, len);
			remove_node(env, var, len);
			free(var);
			len = -1;
		}
		i++;
		len++;
	}
	if (len > 0)
	{
		var = ft_strndup(input + i - len, len);
		remove_node(env, var, len);
		free(var);
	}
}
