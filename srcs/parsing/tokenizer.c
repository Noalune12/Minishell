#include "parsing.h"

#include "minishell.h"

static char	*extract_token(char *input, size_t *pos)
{
	size_t	len;
	char	*token;
	char	*final_token;

	len = get_word_length(input, *pos);
	(void) len;
	token = malloc(sizeof(char) * (len + 1));
	if (token == NULL)
		return (NULL);
	copy_with_quotes(token, input + *pos, &len);
	*pos += len;
	final_token = ft_strdup(token);
	if (final_token == NULL)
	{
		free(token);
		return (NULL);
	}
	free(token);
	return (final_token);
}

static t_token	*token_error(t_token *tokens, char *content, bool *exec_status)
{
	if (content != NULL)
		free(content);
	free_token_list(tokens);
	*exec_status = false;
	return (NULL);
}

static t_token	*process_token(t_token **tokens, t_minishell *shell, size_t *i)
{
	char	*content;

	content = extract_token(shell->input, i);
	if (content == NULL)
		return (token_error(*tokens, NULL, &shell->exec_status));
	if (add_token(&*tokens, content, NODE_COMMAND) == false)
		return (token_error(*tokens, content, &shell->exec_status));
	free(content);
	return (*tokens);
}

void	tokenize_input(t_minishell *minishell)
{
	t_token	*tokens;
	size_t	i;

	if (check_unclosed_quotes(minishell->input) == 0)
	{
		minishell->exec_status = false;
		minishell->exit_status = 2;
		return ;
	}
	tokens = NULL;
	i = 0;
	while (minishell->input[i])
	{
		if (ft_isspace(minishell->input[i]) == true)
			i++;
		else if (process_token(&tokens, minishell, &i) == NULL)
		{
			minishell->exec_status = false;
			minishell->exit_status = 1;
			return ;
		}
	}
	minishell->token = tokens;
	minishell->exec_status = true;
}
