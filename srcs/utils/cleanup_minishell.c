/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:14 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 12:24:51 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "env.h"
#include "minishell.h"
#include "types.h"

static void	close_free_and_reinit_fds(t_fd_info *fd)
{
	int	i;

	i = 0;
	while (i < fd->nb_elems)
	{
		close(fd->fds[i]);
		i++;
	}
	free(fd->fds);
	fd->fds = malloc(sizeof(int) * 10);
	fd->nb_elems = 0;
	fd->capacity = 10;
}

void	cleanup_loop(t_minishell *minishell)
{
	free(minishell->input);
	if (minishell->ast_node)
		ast_free_unlink(minishell);
	if (minishell->fd_in)
		close(minishell->fd_in);
	if (minishell->fd_out)
		close(minishell->fd_out);
	close_free_and_reinit_fds(&minishell->fds.fd_in);
	close_free_and_reinit_fds(&minishell->fds.fd_out);
}

void	cleanup_shell(t_minishell *minishell)
{
	close_and_free_fds(&minishell->fds.fd_in);
	close_and_free_fds(&minishell->fds.fd_out);
	if (minishell->envp != NULL)
		free_list(minishell->envp);
	if (minishell->options != NULL)
		free(minishell->options);
	minishell->envp = NULL;
	minishell->token = NULL;
}

void	cleanup_exit(t_minishell *minishell)
{
	if (minishell->fd_in)
		close(minishell->fd_in);
	if (minishell->fd_out)
		close(minishell->fd_out);
	rl_clear_history();
	cleanup_shell(minishell);
}
