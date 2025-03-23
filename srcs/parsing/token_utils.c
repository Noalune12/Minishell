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
	current = token;
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

t_node_type	get_operator_type(const char *content, \
	size_t i, size_t op_len)
{
	if (ft_strncmp(content + i, "|", op_len) == 0 && op_len == 1)
		return (NODE_PIPE);
	if (ft_strncmp(content + i, "||", op_len) == 0)
		return (NODE_OR);
	if (ft_strncmp(content + i, "&&", op_len) == 0)
		return (NODE_AND);
	if (ft_strncmp(content + i, ">", op_len) == 0 && op_len == 1)
		return (NODE_REDIR_OUT);
	if (ft_strncmp(content + i, "<", op_len) == 0 && op_len == 1)
		return (NODE_REDIR_IN);
	if (ft_strncmp(content + i, ">>", op_len) == 0)
		return (NODE_APPEND);
	if (ft_strncmp(content + i, "<<", op_len) == 0)
		return (NODE_HEREDOC);
	if (ft_strncmp(content + i, "(", op_len) == 0 && op_len == 1)
		return (NODE_OPEN_PAR);
	if (ft_strncmp(content + i, ")", op_len) == 0 && op_len == 1)
		return (NODE_CLOSE_PAR);
	return (NODE_COMMAND);
}

void	handle_quotes(char c, bool *in_quotes, char *quote_type)
{
	if (!*in_quotes)
	{
		*in_quotes = true;
		*quote_type = c;
	}
	else if (c == *quote_type)
	{
		*in_quotes = false;
		*quote_type = 0;
	}
}
