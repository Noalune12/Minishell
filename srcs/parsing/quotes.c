#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

void	copy_with_quotes(char *dest, char *src, size_t *len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i] && src[i] != ' ' && src[i] != '\t')
	{
		if (is_quote(src[i]))
		{
			dest[j++] = src[i++];
			while (src[i] && !is_quote(src[i]))
				dest[j++] = src[i++];
			if (src[i])
				dest[j++] = src[i++];
		}
		else
			dest[j++] = src[i++];
	}
	dest[j] = '\0';
	*len = i;
}

void	count_quoted_length(char *input, size_t *i)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i])
		(*i)++;
}

size_t	get_word_length(char *input, size_t start)
{
	size_t	i;

	i = 0;
	while (input[start + i] && input[start + i] != ' ' && input[start + i] != '\t')
	{
		if (is_quote(input[start + i]))
			count_quoted_length(input + start, &i);
		else
			i++;
	}
	return (i);
}
