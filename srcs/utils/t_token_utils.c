#include "libft.h"
#include "minishell.h"
#include "types.h"

t_token	*init_token_node(char *content, t_node_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->content = ft_strdup(content);
	if (token->content == NULL)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->to_expand = true;
	token->next = NULL;
	return (token);
}

bool	add_token(t_token **tokens, char *content, t_node_type type)
{
	t_token	*new;
	t_token	*last;

	new = init_token_node(content, type);
	if (!new)
		return (false);
	if (!*tokens)
		*tokens = new;
	else
	{
		last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (true);
}

bool	add_token_in_place(t_token **tokens, char *content, t_node_type type)
{
	t_token	*new;

	new = init_token_node(content, type);
	if (new == NULL)
		return (false);
	if (*tokens == NULL)
		*tokens = new;
	else
	{
		new->next = (*tokens)->next;
		(*tokens)->next = new;
	}
	return (true);
}
