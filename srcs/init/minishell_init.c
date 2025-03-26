/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:22:17 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 09:25:55 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "env.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "minishell.h"
#include "options.h"
#include "utils.h"

void	tty_check(void)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		ft_dprintf(STDERR_FILENO, NOT_A_TTY);
		exit(EXIT_FAILURE);
	}
}

static void	init_options(t_minishell *minishell)
{
	minishell->options = malloc(sizeof(t_options));
	if (minishell->options == NULL)
	{
		free_list(minishell->envp);
		ft_dprintf(STDERR_FILENO, MEM_ALLOC_ERR);
		exit(EXIT_FAILURE);
	}
	minishell->options->display_ast = false;
	minishell->options->display_tokens = false;
}

static bool	init_fd_info(t_fd_info *fd)
{
	fd->fds = malloc(sizeof(int) * 10);
	if (!fd->fds)
		return (0);
	fd->nb_elems = 0;
	fd->capacity = 10;
	return (1);
}

void	minishell_init(t_minishell *minishell, int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	tty_check();
	ft_memset(minishell, 0, sizeof(t_minishell));
	minishell->exec = av[0];
	minishell->envp = env_init(envp);
	if (minishell->envp == NULL)
		exit(EXIT_FAILURE);
	minishell->pid = -1;
	init_options(minishell);
	if (init_fd_info(&minishell->fds.fd_in) == 0
		|| init_fd_info(&minishell->fds.fd_out) == 0)
	{
		cleanup_shell(minishell);
		ft_dprintf(STDERR_FILENO, MEM_ALLOC_ERR);
		exit(EXIT_FAILURE);
	}
}
