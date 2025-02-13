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
	free(token);
	return (final_token);
}

t_list	*tokenize_input(char *input)
{
	t_list	*tokens;
	size_t	i;
	char	*token;

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
			token = extract_token(input, &i);
			if (!token)
			{
				free_list(tokens);
				return (NULL);
			}
			add_node(&tokens, token);
			free(token);
		}
	}
	return (tokens);
}
