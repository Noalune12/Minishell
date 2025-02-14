#include "minishell.h"

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

t_list	*handle_operator_error(t_list *tokens, const char *op)
{
	clear_token_list(tokens);
	ft_printf(STRING_SYNTAX, op);
	return (NULL);
}
