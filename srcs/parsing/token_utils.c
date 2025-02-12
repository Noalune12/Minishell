#include "minishell.h"

void	clear_token_list(t_list *token)
{
	t_list	*current;
	t_list	*next;

	if (!token)
		return ;
	current = token->next;
	token->next = NULL; // Réinitialise le pointeur next du premier nœud
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
}

int	add_token_to_list(t_list **tokens, char *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->content = ft_strdup(content);
	if (!new->content)
	{
		free (new);
		return (0);
	}
	new->next = NULL;
	if (!*tokens)
		*tokens = new;
	else
		add_node(tokens, content);
	return (1);
}
