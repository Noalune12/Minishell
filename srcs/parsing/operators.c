#include "minishell.h"

static bool	handle_operator(t_list **tokens, const char *str, \
	size_t *i, size_t *start)
{
	t_redirect_error	error;
	size_t				op_len;

	if (*i > *start && !add_token_to_list(tokens, \
		create_token(str, *start, *i - *start)))
		return (false);
	op_len = get_operator_len(str, *i);
	error = check_operator_syntax(str + *i);
	if (error != REDIR_SUCCESS)
	{
		handle_redirect_error(*tokens, error, str + *i);
		return (false);
	}
	if (!add_token_to_list(tokens, create_token(str, *i, op_len)))
		return (false);
	*i += op_len;
	*start = *i;
	return (true);
}

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

static void	init_split_vars(bool *in_quotes, char *quote_type)
{
	*in_quotes = false;
	*quote_type = 0;
}

t_list	*split_operators(const char *str, size_t i, size_t start)
{
	t_list	*tokens;
	bool	in_quotes;
	char	quote_type;

	tokens = NULL;
	init_split_vars(&in_quotes, &quote_type);
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			handle_quotes(str[i], &in_quotes, &quote_type);
			i++;
		}
		else if (is_operator(str[i], in_quotes))
		{
			if (!handle_operator(&tokens, str, &i, &start))
				return (NULL);
		}
		else
			i++;
	}
	if (i > start && !add_token_to_list(&tokens, \
		create_token(str, start, i - start)))
		return (NULL);
	return (tokens);
}
