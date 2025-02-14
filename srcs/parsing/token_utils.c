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


t_list	*handle_redirect_error(t_list *tokens, t_redirect_error error,
	const char *token)
{
	clear_token_list(tokens);
	print_redirect_error(error, token);
	return (NULL);
}

t_list	*split_operators(const char *str)
{
	t_list			*tokens;
	size_t			i;
	size_t			start;
	size_t			op_len;
	t_redirect_error	error;

	tokens = NULL;
	i = 0;
	start = 0;
	while (str[i])
	{
		if (is_operator_char(str[i]))
		{
			error = check_operator_syntax(str, i);
			if (error != REDIR_SUCCESS)
				return (handle_redirect_error(tokens, error, str + i));
			if (i > start && !add_token_to_list(&tokens,
				create_token(str, start, i - start)))
				return (NULL);
			op_len = get_operator_len(str, i);
			if (!add_token_to_list(&tokens, create_token(str, i, op_len)))
				return (NULL);
			i += op_len;
			start = i;
		}
		else
			i++;
	}
	if (i > start && !add_token_to_list(&tokens,
		create_token(str, start, i - start)))
		return (NULL);
	return (tokens);
}
