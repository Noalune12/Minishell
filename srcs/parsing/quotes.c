#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	check_unclosed_quotes(char *input)
{
	size_t	i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
			{
				dprintf(STDERR_FILENO, CHAR_SYNTAX, quote); // a changer
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	copy_with_quotes(char *dest, char *src, size_t *len)
{
	size_t	i;
	size_t	j;
	char	current_quote;

	i = 0;
	j = 0;
	current_quote = 0;
	while (src[i] && src[i] != ' ' && src[i] != '\t')
	{
		if (is_quote(src[i]) && !current_quote)
		{
			current_quote = src[i];
			dest[j++] = src[i++];
		}
		else if (src[i] == current_quote)
		{
			current_quote = 0;
			dest[j++] = src[i++];
		}
		else
			dest[j++] = src[i++];
	}
	dest[j] = '\0';
	*len = i;
}
