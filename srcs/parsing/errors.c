#include "minishell.h"

void	print_redirect_error(t_redirect_error error, const char *token)
{
	if (error == REDIR_UNEXPECTED_NEWLINE)
		ft_dprintf(STDERR_FILENO, "syntax error near unexpected token `newline'\n");
	else if (error == REDIR_UNEXPECTED_TOKEN && token)
		ft_dprintf(STDERR_FILENO, "syntax error near unexpected token `%s'\n", token);
	else if (error == REDIR_MISSING_FILENAME)
		ft_dprintf(STDERR_FILENO, "syntax error: missing filename after redirection\n");
	else if (error == REDIR_FILE_ERROR && token)
		ft_dprintf(STDERR_FILENO, "%s: No such file or directory\n", token);
	else if (error == REDIR_HEREDOC_EOF && token)
		ft_dprintf(STDERR_FILENO, "warning: here-document delimited by end-of-file (wanted `%s')\n",
			token);
	else if (error == REDIR_SYNTAX_ERROR)
		ft_dprintf(STDERR_FILENO, "syntax error\n");
}

t_list	*handle_redirect_error(t_list *tokens, t_redirect_error error,
	const char *token)
{
	clear_token_list(tokens);
	print_redirect_error(error, token);
	return (NULL);
}
