/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:06:15 by gueberso          #+#    #+#             */
/*   Updated: 2025/07/24 14:47:37 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

static int	copy_strings_segment(t_new_array *n_array, char **src, \
			int src_start, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		n_array->new_cmds[n_array->dest_index] = ft_strdup(src[src_start + i]);
		if (!n_array->new_cmds[n_array->dest_index])
			return (0);
		i++;
		n_array->dest_index++;
	}
	return (1);
}

static int	get_old_len(char **old_cmds)
{
	int	old_len;

	old_len = 0;
	while (old_cmds[old_len])
		old_len++;
	return (old_len);
}

char	**create_new_cmds_array(char **old_cmds, int old_index, \
	char **file_names, int file_count)
{
	t_new_array	n_array;

	n_array.old_len = get_old_len(old_cmds);
	n_array.new_len = n_array.old_len - 1 + file_count;
	n_array.new_cmds = malloc(sizeof(char *) * (n_array.new_len + 1));
	if (!n_array.new_cmds)
		return (NULL);
	n_array.dest_index = 0;
	if (!copy_strings_segment(&n_array, old_cmds, 0, old_index)
		|| !copy_strings_segment(&n_array, file_names, 0, file_count)
		|| !copy_strings_segment(&n_array, old_cmds, old_index + 1, \
			n_array.old_len - old_index - 1))
	{
		ft_free_double(n_array.new_cmds);
		return (NULL);
	}
	n_array.new_cmds[n_array.new_len] = NULL;
	return (n_array.new_cmds);
}
