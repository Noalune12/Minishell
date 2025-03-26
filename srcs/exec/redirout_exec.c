/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirout_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:22:10 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 13:37:45 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>

#include "ast.h"
#include "exec.h"
#include "ft_dprintf.h"
#include "minishell.h"

int	handle_redirout(t_ast *node, t_minishell *minishell)
{
	int	ret;
	int	fd;

	fd = open(node->cmd->cmds[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, SIMPLE_ERR, node->cmd->cmds[0]);
		perror("");
		return (1);
	}
	if (add_fd(&minishell->fds.fd_out, fd) == NULL)
	{
		close(fd);
		return (1);
	}
	ret = exec_minishell(node->left, minishell);
	delete_fd(&minishell->fds.fd_out, minishell->fds.fd_out.nb_elems - 1);
	close(fd);
	return (ret);
}
