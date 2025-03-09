#include "minishell.h"

bool	contains_wildards(char *token)
{
	bool	in_squotes;
	bool	in_dquotes;
	size_t	i;

	if (!token)
		return (false);
	in_squotes = false;
	in_dquotes = false;
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' && !in_dquotes)
			in_squotes = !in_squotes;
		else if (token[i] == '\'' && !in_squotes)
			in_dquotes = !in_dquotes;
		else if (token[i] = '*' && !in_dquotes && !in_squotes)
			return (true);
		i++;
	}
	return (false);
}
