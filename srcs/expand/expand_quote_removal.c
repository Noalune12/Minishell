#include <stdlib.h>

#include "expand.h"
#include "libft.h"

static bool	is_quote_to_remove(char c, bool in_squotes, bool in_dquotes)
{
	// printf("in_squotes: %d\nin_dquotes: %d\n", in_squotes, in_dquotes);
	if (c == '\'' && !in_dquotes)
		return (true);
	if (c == '"' && !in_squotes)
		return (true);
	return (false);
}

char	*remove_quotes(char *str)
{
	char	*result;
	size_t	i;
	size_t	j;
	bool	in_squotes;
	bool	in_dquotes;

	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_squotes = false;
	in_dquotes = false;
	while (str[i])
	{
		if (is_quote_to_remove(str[i], in_squotes, in_dquotes))
		{
			if (str[i] == '\'')
				in_squotes = !in_squotes;
			else if (str[i] == '"')
				in_dquotes = !in_dquotes;
		}
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
