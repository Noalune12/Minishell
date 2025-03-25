#include "minishell.h"
#include "parsing.h"

t_redirect_error	check_operator_syntax(const char *str)
{
	if (!str[0])
		return (REDIR_UNEXPECTED_NEWLINE);
	if (str[0] == '&' && !str[1])
		return (REDIR_UNEXPECTED_NEWLINE);
	if ((str[0] == '>' && str[1] == '>' && str[2] == '>')
		|| (str[0] == '<' && str[1] == '<' && str[2] == '<'))
		return (REDIR_UNEXPECTED_TOKEN);
	return (REDIR_SUCCESS);
}

t_list	*handle_operator_error(t_list *tokens, const char *op)
{
	clear_token_list(tokens);
	ft_dprintf(STDERR_FILENO, STR_SYNTAX, op);
	return (NULL);
}
