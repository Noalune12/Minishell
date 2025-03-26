/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:29 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 13:04:58 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>

#include "ast.h"
#include "exec.h"
#include "ft_dprintf.h"
#include "libft.h"

static int	check_cmd_content(t_ast *node)
{
	if (!node->cmd->cmds[0][0])
	{
		ft_dprintf(STDERR_FILENO, CMD_NOT_FOUND, "");
		return (127);
	}
	if (ft_strcmp(node->cmd->cmds[0], ".") == 0)
	{
		ft_dprintf(STDERR_FILENO, DOT_ERR, node->cmd->cmds[0]);
		return (2);
	}
	return (0);
}

int	check_cmd(t_ast *node)
{
	struct stat	path;
	int			ret;

	ret = check_cmd_content(node);
	if (ret != 0)
		return (ret);
	if (stat(node->cmd->cmds[0], &path) == 0)
	{
		if (path.st_mode && start_as_file(node) == 1 && S_ISDIR(path.st_mode))
		{
			ft_dprintf(STDERR_FILENO, IS_REDIR, node->cmd->cmds[0]);
			return (126);
		}
		if (path.st_mode && start_as_file(node) == 1 && !S_ISREG(path.st_mode))
		{
			ft_dprintf(STDERR_FILENO, SIMPLE_ERR, node->cmd->cmds[0]);
			perror("");
			return (127);
		}
	}
	return (0);
}
