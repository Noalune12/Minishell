#include <stdbool.h>

static bool	handle_squote_start(bool *in_squotes, int *quote)
{
	if (quote)
		*quote = 1;
	*in_squotes = true;
	return (false);
}

static bool	handle_dquote_start(bool *in_dquotes, int *quote)
{
	if (quote)
		*quote = 1;
	*in_dquotes = true;
	return (true);
}

bool	update_quotes_expand(char c, bool *in_squotes, bool *in_dquotes,
			int *quote)
{
	if (c == '\'' && !*in_squotes && !*in_dquotes)
		return (handle_squote_start(in_squotes, quote));
	if (c == '\'' && *in_squotes)
	{
		*in_squotes = false;
		return (false);
	}
	if (c == '"' && !*in_squotes && !*in_dquotes)
		return (handle_dquote_start(in_dquotes, quote));
	if (c == '"' && *in_dquotes)
	{
		*in_dquotes = false;
		return (true);
	}
	if (*in_squotes)
		return (false);
	return (true);
}
