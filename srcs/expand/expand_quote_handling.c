#include <stdbool.h>

bool	handle_quotes_expand(char c, bool *in_squotes, bool *in_dquotes, int *quote)
{
	if (c == '\'' && !*in_squotes && !*in_dquotes)
	{
		if (quote)
			*quote = 1;
		*in_squotes = true;
		return (false);
	}
	else if (c == '\'' && *in_squotes)
	{
		*in_squotes = false;
		return (false);
	}
	else if (c == '"' && !*in_squotes && !*in_dquotes)
	{
		if (quote)
			*quote = 1;
		*in_dquotes = true;
		return (true);
	}
	else if (c == '"' && *in_dquotes)
	{
		*in_dquotes = false;
		return (true);
	}
	if (*in_squotes)
		return (false);
	return (true);
}
