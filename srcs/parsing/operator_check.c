#include "minishell.h"

t_redirect_error	check_operator_syntax(const char *str, size_t pos)
{
	char	curr;
	char	next;

	curr = str[pos];
	next = str[pos + 1];
	if (!next)
		return (REDIR_UNEXPECTED_NEWLINE);
	if (curr == '>' && next == '>' && str[pos + 2] == '>')
		return (REDIR_UNEXPECTED_TOKEN);
	if (curr == '<' && next == '<' && str[pos + 2] == '<')
		return (REDIR_UNEXPECTED_TOKEN);
	if ((curr == '>' && next != '>') && str[pos + 1] == '>')
		return (REDIR_UNEXPECTED_TOKEN);
	if ((curr == '<' && next != '<') && str[pos + 1] == '<')
		return (REDIR_UNEXPECTED_TOKEN);
	return (REDIR_SUCCESS);
}

t_list	*handle_operator_error(t_list *tokens, const char *op)
{
	clear_token_list(tokens);
	ft_printf(STRING_SYNTAX, op);
	return (NULL);
}

