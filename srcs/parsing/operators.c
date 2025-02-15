#include "minishell.h"

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

bool	is_operator_char(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&')
		return (true);
	return (false);
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
