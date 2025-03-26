/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:38 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 09:21:39 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_redirection(char c)
{
	return (c == '<' || c == '>');
}

bool	is_operator(char c, bool in_quotes)
{
	if (in_quotes)
		return (false);
	return (c == '|' || c == '<' || c == '>' || c == '&' \
		|| c == '(' || c == ')');
}

size_t	get_operator_len(const char *str, size_t pos)
{
	char	curr;
	char	next;

	curr = str[pos];
	next = str[pos + 1];
	if (!next)
		return (1);
	if ((curr == '>' && next == '>')
		|| (curr == '<' && next == '<')
		|| (curr == '|' && next == '|')
		|| (curr == '&' && next == '&'))
		return (2);
	return (1);
}
