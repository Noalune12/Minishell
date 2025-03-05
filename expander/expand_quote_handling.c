#include "expand.h"

bool	handle_quotes_expand(char c, bool *in_squotes, bool *in_dquotes)
{
	if (c == '\'' && !*in_squotes && !*in_dquotes)
	{
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
