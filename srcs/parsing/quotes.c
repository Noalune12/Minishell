#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	check_quote(char *input) // change for boolean later ?
{
	char	opened_quote;
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			opened_quote = input[i];
			i++;
			while (input[i] && input[i] != opened_quote)
				i++;
			if (!input[i])
			{
				dprintf(STDERR_FILENO, "minishell: error: unclosed quotes\n"); // a modifier pour notre propre printf
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	copy_without_quotes(char *dest, char *src, size_t *len)
{
	size_t	i;
	size_t	j;
	char	quote;

	i = 0;
	j = 0;
	while (src[i] && (src[i] != ' ' || src[i] != '\t'))
	{
		if (is_quote(src[i]))
		{
			quote = src[i];
			i++;
			while (src[i] && src[i] != quote)
				dest[j++] = src[i++];
			if (src[i])
				i++;
		}
		else
			dest[j++] = src[i++];
	}
	dest[j] = '\0';
	*len = i;
}

char	*get_unquoted_content(char *input, size_t *i)
{
	char	*res;
	size_t	start;
	size_t	len;

	start = *i;
	len = 0;
	while (input[start + len] && !is_quote(input[start + len]) \
		&& (input[start + len] != ' ' || input[start + len] != '\t'))
		len++;
	res = ft_substr(input, start, len);
	if (!res)
		return (NULL);
	*i = start + len;
	return (res);
}

size_t	get_word_length(char *input, size_t start)
{
	size_t	i;
	char	quote;

	i = 0;
	while (input[start + i] && (input[start + i] != ' ' \
		|| input[start + i] != '\t'))
	{
		if (is_quote(input[start + i]))
		{
			quote = input[start + i];
			i++;
			while (input[start + i] && input[start + i] != quote)
				i++;
			if (input[start + i])
				i++;
		}
		else
			i++;
	}
	return (i);
}
