#include "minishell.h"

bool	replace_token(t_list *current, t_list *new_tokens)
{
	t_list	*next;
	t_list	*new_next;

	if (!new_tokens)
		return (true);
	next = current->next;
	free(current->content);
	current->content = ft_strdup(new_tokens->content);
	if (!current->content)
		return (false);
	current->next = new_tokens->next;
	free(new_tokens);
	if (!current->next)
	{
		current->next = next;
		return (true);
	}
	new_next = ft_lstlast(current->next);
	new_next->next = next;
	return (true);
}
