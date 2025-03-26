/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:49 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 13:32:46 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>

#include "ast.h"
#include "exec.h"
#include "expand.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "minishell.h"

static int	error_handling_heredoc(char *filename, char *str, int fd)
{
	if (filename)
	{
		ft_dprintf(STDERR_FILENO, SIMPLE_ERR, filename);
		perror("");
	}
	if (str)
		free(str);
	if (fd != -1)
		close(fd);
	return (1);
}

static int	get_content(int fd, char **content, char *filename)
{
	char	buffer[READ_LEN + 1];
	ssize_t	b_read;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, READ_LEN);
		if (b_read == 0)
			break ;
		if (b_read == -1)
			return (error_handling_heredoc(filename, *content, fd));
		buffer[b_read] = '\0';
		if (*content == NULL)
			*content = ft_strndup(buffer, b_read);
		else
			*content = ft_strjoin_free_s1(*content, buffer);
		if (*content == NULL)
			return (error_handling_heredoc(NULL, NULL, fd));
	}
	return (0);
}

static int	write_in_heredoc(char *filename, char *expanded)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_TRUNC);
	if (fd == -1)
		return (error_handling_heredoc(filename, expanded, -1));
	if (write(fd, expanded, ft_strlen(expanded)) == -1)
		return (error_handling_heredoc(filename, expanded, fd));
	free(expanded);
	close(fd);
	return (0);
}

static int	open_and_replace(char *filename, t_minishell *minishell)
{
	char	*content;
	int		fd;
	char	*expanded;

	content = NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, SIMPLE_ERR, filename);
		perror("");
		return (1);
	}
	if (get_content(fd, &content, filename) == 1)
		return (1);
	close(fd);
	expanded = expand_heredoc(content, minishell);
	free(content);
	if (expanded == NULL)
		return (error_handling_heredoc(NULL, NULL, -1));
	if (write_in_heredoc(filename, expanded) == 1)
		return (1);
	return (0);
}

int	handle_heredocin(t_ast *node, t_minishell *minishell)
{
	int	ret;
	int	fd;

	if (node->cmd->to_expand == true)
	{
		if (open_and_replace(node->cmd->cmds[0], minishell) == 1)
			return (1);
	}
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
