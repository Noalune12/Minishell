#include "minishell.h"

static char	*extract_token(char *input, size_t *pos)
{
	size_t	len;
	char	*token;
	char	*final_token;

	len = get_word_length(input, *pos);
	token = malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);
	copy_with_quotes(token, input + *pos, &len);
	*pos += len;
	final_token = ft_strdup(token);
	if (!final_token)
	{
		free(token);
		return (NULL);
	}
	free(token);
	return (final_token);
}

static t_token	*handle_tokenization_error(t_token *tokens, char *content,
										bool *exec_status)
{
	if (content)
		free(content);
	free_token_list(tokens);
	*exec_status = false;
	return (NULL);
}

static t_token	*process_token(t_token *tokens, char *input, size_t *i,
							bool *exec_status)
{
	char	*content;

	content = extract_token(input, i);
	if (content == NULL)
		return (handle_tokenization_error(tokens, NULL, exec_status));
	if (add_token(&tokens, content, NODE_COMMAND) == false)
		return (handle_tokenization_error(tokens, content, exec_status));
	free(content);
	return (tokens);
}

t_token	*tokenize_input(char *input, bool *exec_status)
{
	t_token	*tokens;
	size_t	i;

	if (!check_unclosed_quotes(input))
	{
		*exec_status = false;
		return (NULL);
	}
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (!(tokens = process_token(tokens, input, &i, exec_status)))
			return (NULL);
	}
	*exec_status = true;
	return (tokens);
}
