#include "minishell.h"

char	*extract_token(char *input, size_t *pos)
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

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	size_t	i;
	char	*content;

	if (!check_unclosed_quotes(input))
		return (NULL);
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else
		{
			content = extract_token(input, &i);
			if (!content)
			{
				free_token_list(tokens);
				return (NULL);
			}
			if (!add_token(&tokens, content, NODE_COMMAND))
			{
				free(content);
				free_token_list(tokens);
				return (NULL);
			}
			free(content);
		}
	}
	return (tokens);
}

// t_list	*tokenize_input(char *input)
// {
// 	t_list	*tokens;
// 	size_t	i;
// 	char	*content;

// 	if (!check_unclosed_quotes(input))
// 		return (NULL);
// 	tokens = NULL;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == ' ' || input[i] == '\t')
// 			i++;
// 		else
// 		{
// 			content = extract_token(input, &i);
// 			if (!content)
// 			{
// 				free_list(tokens);
// 				return (NULL);
// 			}
// 			add_node(&tokens, content);
// 			free(content);
// 		}
// 	}
// 	return (tokens);
// }
