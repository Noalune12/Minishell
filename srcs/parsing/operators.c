#include "minishell.h"

static void	init_split_vars(size_t *i, size_t *start, bool *in_quotes, \
	char *quote_type)
{
	*i = 0;
	*start = 0;
	*in_quotes = false;
	*quote_type = 0;
}

static bool	handle_operator(t_list **tokens, const char *str, \
	size_t *i, size_t *start)
{
	t_redirect_error	error;
	size_t			op_len;

	error = check_operator_syntax(str, *i);
	if (error != REDIR_SUCCESS)
	{
		handle_redirect_error(*tokens, error, str + *i);
		return (false);
	}
	if (*i > *start && !add_token_to_list(tokens, \
		create_token(str, *start, *i - *start)))
		return (false);
	op_len = get_operator_len(str, *i);
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

t_list	*split_operators(const char *str)
{
	t_list	*tokens;
	size_t	i;
	size_t	start;
	bool	in_quotes;
	char	quote_type;

	tokens = NULL;
	init_split_vars(&i, &start, &in_quotes, &quote_type);
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			handle_quotes(str[i], &in_quotes, &quote_type);
			i++;
		}
		else if (is_operator_char(str[i], in_quotes))
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

bool	is_operator_char(char c, bool in_quotes)
{
	if (in_quotes)
		return (false);
	return (c == '|' || c == '<' || c == '>' || c == '&' \
		|| c == '(' || c == ')');
}

size_t	get_operator_len(const char *str, size_t pos)
{
	char	curr;
	char	next;

	curr = str[pos];
	next = str[pos + 1];
	if (!next)
		return (1);
	if ((curr == '>' && next == '>') || (curr == '<' && next == '<')
		|| (curr == '|' && next == '|') || (curr == '&' && next == '&'))
		return (2);
	return (1);
}
