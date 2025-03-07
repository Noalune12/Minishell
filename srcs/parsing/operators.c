#include "minishell.h"

static void	handle_quotes(char c, bool *in_quotes, char *quote_type)
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

static t_node_type	get_operator_type(const char *content, \
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

static bool	handle_first_part(t_token **result, const char *content,
							size_t *i, size_t *start)
{
	char	*str;

	if (*i <= *start)
		return (true);
	str = ft_strndup(content + *start, *i - *start);
	if (!str)
		return (false);
	if (!add_token(result, str, NODE_COMMAND))
	{
		free(str);
		return (false);
	}
	return (true);
}

static bool	process_operator(t_token **result, const char *content,
							size_t *i, size_t *start)
{
	size_t		op_len;
	t_node_type	op_type;
	char		*str;

	if (!handle_first_part(result, content, i, start))
		return (false);
	op_len = get_operator_len(content, *i);
	op_type = get_operator_type(content, *i, op_len);
	str = ft_strndup(content + *i, op_len);
	if (!str)
		return (false);
	if (!add_token(result, str, op_type))
	{
		free(str);
		return (false);
	}
	*i += op_len;
	*start = *i;
	free(str);
	return (true);
}

static bool	process_token_content(t_token **result, const char *content)
{
	size_t	i;
	size_t	start;
	bool	in_quotes;
	char	quote_type;
	char	*str;

	i = 0;
	start = 0;
	in_quotes = false;
	quote_type = 0;
	while (content[i])
	{
		if (is_quote(content[i]))
			handle_quotes(content[i++], &in_quotes, &quote_type);
		else if (!in_quotes && is_operator(content[i], false))
		{
			if (!process_operator(result, content, &i, &start))
				return (false);
		}
		else
			i++;
	}
	if (i <= start)
		return (true);
	str = ft_strndup(content + start, i - start);
	if (!str)
		return (false);
	if (!add_token(result, str, NODE_COMMAND))
	{
		free(str);
		return (false);
	}
	free(str);
	return (true);
}

t_token	*split_operators(t_token *tokens)
{
	t_token	*result;
	t_token	*current;
	t_token	*next;

	result = NULL;
	current = tokens;
	while (current)
	{
		if (!process_token_content(&result, current->content))
		{
			free_token_list(result);
			return (NULL);
		}
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	return (result);
}
