/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:00:00 by gueberso          #+#    #+#             */
/*   Updated: 2025/07/24 15:49:25 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "wildcard.h"

int	count_wildcard_matches(char *pattern)
{
	int	count;

	if (!pattern || !contain_wildcard(pattern))
		return (1);
	count = count_matches(pattern);
	if (count == 0)
		return (1);
	return (count);
}

char	**expand_wildcard_in_cmds(char **cmds, int index)
{
	char	**file_names;
	char	**new_cmds;
	int		count;

	if (!cmds || !cmds[index] || !contain_wildcard(cmds[index]))
		return (cmds);
	count = count_matches(cmds[index]);
	if (count <= 0)
		return (cmds);
	file_names = get_file_names(cmds[index], count);
	if (!file_names)
		return (cmds);
	new_cmds = create_new_cmds_array(cmds, index, file_names, count);
	ft_free_double(file_names);
	if (!new_cmds)
		return (cmds);
	ft_free_double(cmds);
	return (new_cmds);
}

bool	is_ambiguous_redirect(char *original_pattern)
{
	int	count;

	if (!original_pattern || !contain_wildcard(original_pattern))
		return (false);
	count = count_matches(original_pattern);
	return (count != 1);
}
