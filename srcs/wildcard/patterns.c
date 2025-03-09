#include "minishell.h"

static bool	wildcard_match_end(const char *pattern, const char *str)
{
	if (*pattern == '\0')
		return (*str == '\0');
	return (false);
}

static bool	wildcard_match_star(const char *pattern, const char *str)
{
	if (wildcard_match(pattern + 1, str))
		return (true);
	if (*str != '\0' && wildcard_match(pattern, str + 1))
		return (true);
	return (false);
}

static bool	wildcard_match_char(const char *pattern, const char *str)
{
	if (*str != '\0' && *pattern == *str)
		return (wildcard_match(pattern + 1, str + 1));
	return (false);
}

bool	wildcard_match(const char *pattern, const char *str)
{
	if (*pattern == '\0')
		return (wildcard_match_end(pattern, str));
	if (*pattern == '*')
		return (wildcard_match_star(pattern, str));
	return (wildcard_match_char(pattern, str));
}
