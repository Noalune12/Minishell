#include "minishell.h"
#include "parsing.h"

void	print_redirect_error(t_redirect_error error, const char *token)
{
	if (error == REDIR_UNEXPECTED_NEWLINE)
		ft_dprintf(STDERR_FILENO, NEWLINE_SYNTAX);
	else if (error == REDIR_UNEXPECTED_TOKEN && token)
		ft_dprintf(STDERR_FILENO, STR_SYNTAX, token);
	else if (error == REDIR_MISSING_FILENAME)
		ft_dprintf(STDERR_FILENO, FILENAME_SYNTAX);
	else if (error == REDIR_FILE_ERROR && token)
		ft_dprintf(STDERR_FILENO, FILE_NOT_FOUND, "COMMANDE ICI !!!", token);
	else if (error == REDIR_HEREDOC_EOF && token)
		ft_dprintf(STDERR_FILENO, HEREDOC_ERROR_MESSAGE, token);
	else if (error == REDIR_SYNTAX_ERROR)
		ft_dprintf(STDERR_FILENO, ERROR_SYNTAX_TO_MODIFY);
}

t_list	*handle_redirect_error(t_list *tokens, t_redirect_error error,
	const char *token)
{
	print_redirect_error(error, token);
	clear_token_list(tokens);
	return (NULL);
}
