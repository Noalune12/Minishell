/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:23 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 09:21:24 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

size_t	get_word_length(char *input, size_t start)
{
	size_t	i;
	bool	in_quotes;
	char	quote_type;

	i = 0;
	in_quotes = false;
	quote_type = 0;
	while (input[start + i])
	{
		if (is_quote(input[start + i]))
		{
			if (!in_quotes)
			{
				in_quotes = true;
				quote_type = input[start + i];
			}
			else if (input[start + i] == quote_type)
				in_quotes = false;
		}
		else if (!in_quotes && ft_isspace(input[start + i]))
			break ;
		i++;
	}
	return (i);
}
