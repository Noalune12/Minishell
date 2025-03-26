/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:02 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 09:21:03 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	wildcard_match(const char *pattern, const char *str);

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
	{
		while (*(pattern + 1) == '*')
			pattern++;
		return (wildcard_match_star(pattern, str));
	}
	return (wildcard_match_char(pattern, str));
}
