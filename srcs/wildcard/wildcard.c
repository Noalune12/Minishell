#include "minishell.h"

t_token	*expand_wildcards(t_token *tokens, bool *exec_status)
{
	t_token	*current;
	t_token	*next;

	if (*exec_status == false)
		return (NULL);
	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->type == NODE_COMMAND && contains_wildcard(current->content))
		{
			if (!expand_token_wildcard(current))
			{
				free_token_list(tokens);
				*exec_status = false;
				return (NULL);
			}
		}
		current = next;
	}
	return (tokens);
}
