/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:22:08 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 09:22:09 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>

#include "ast.h"
#include "exec.h"
#include "ft_dprintf.h"
#include "minishell.h"

int	handle_redirin(t_ast *node, t_minishell *minishell)
{
	int	ret;
	int	fd;

	fd = open(node->cmd->cmds[0], O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, SIMPLE_ERR, node->cmd->cmds[0]);
		perror("");
		return (1);
	}
	if (add_fd(&minishell->fds.fd_in, fd) == NULL)
	{
		close(fd);
		return (1);
	}
	ret = exec_minishell(node->left, minishell);
	delete_fd(&minishell->fds.fd_in, minishell->fds.fd_in.nb_elems - 1);
	close(fd);
	return (ret);
}
