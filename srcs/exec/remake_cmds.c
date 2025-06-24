/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remake_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:22:13 by lbuisson          #+#    #+#             */
/*   Updated: 2025/06/22 19:03:19 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

static int	fill_new_cmds(char **cmds, int *index, char **new_cmd, char **ret)
{
	int		i;
	int		k;
	int		j;

	i = -1;
	while (++i < *index)
		ret[i] = cmds[i];
	j = -1;
	while (new_cmd[++j])
	{
		ret[*index] = new_cmd[j];
		(*index)++;
	}
	k = *index;
	i++;
	while (cmds[i])
	{
		ret[k] = cmds[i];
		i++;
		k++;
	}
	ret[k] = NULL;
	return (0);
}

char	**remake_cmds(char **cmds, int *index)
{
	char	**new_cmd;
	int		cmds_len;
	int		new_cmd_len;
	char	**ret;

	new_cmd = ft_split_charset(cmds[*index], IFS_CHARACTERS);
	if (new_cmd == NULL)
		return (NULL);
	cmds_len = 0;
	new_cmd_len = 0;
	while (cmds[cmds_len])
		cmds_len++;
	while (new_cmd[new_cmd_len])
		new_cmd_len++;
	ret = malloc((cmds_len + new_cmd_len) * sizeof(char *));
	if (ret == NULL)
	{
		ft_free_double(new_cmd);
		return (NULL);
	}
	fill_new_cmds(cmds, index, new_cmd, ret);
	(*index)--;
	free(cmds);
	free(new_cmd);
	return (ret);
}
