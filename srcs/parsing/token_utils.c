#include "minishell.h"

char	*create_token(const char *str, size_t start, size_t len)
{
	char	*token;
	size_t	i;

	token = malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);
	i = 0;
	while (i < len)
	{
		token[i] = str[start + i];
		i++;
	}
	token[i] = '\0';
	return (token);
}

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

bool	add_token_to_list(t_list **tokens, char *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
	{
		free(content);
		return (false);
	}
	ft_lstadd_back(tokens, new);
	return (true);
}
