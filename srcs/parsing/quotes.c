#include "common.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	check_unclosed_quotes(char *input)
{
	size_t	i;
	char	current_quote;

	i = 0;
	current_quote = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			if (!current_quote)
				current_quote = input[i];
			else if (input[i] == current_quote)
				current_quote = 0;
		}
		i++;
	}
	if (current_quote)
	{
		ft_dprintf(STDERR_FILENO, CHAR_SYNTAX, current_quote);
		return (0);
	}
	return (1);
}

void	copy_with_quotes(char *dest, char *src, size_t *len)
{
	size_t	i;
	size_t	j;
	bool	in_quotes;
	char	quote_type;

	i = 0;
	j = 0;
	in_quotes = false;
	quote_type = 0;
	while (src[i])
	{
		if (is_quote(src[i]) && !in_quotes)
		{
			in_quotes = true;
			quote_type = src[i];
		}
		else if (is_quote(src[i]) && src[i] == quote_type)
			in_quotes = false;
		else if (!in_quotes && ft_isspace(src[i]))
			break ;
		dest[j++] = src[i++];
	}
	dest[j] = '\0';
	*len = i;
}
