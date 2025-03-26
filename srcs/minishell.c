/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:54 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 09:20:55 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>

#include "ast.h"
#include "heredoc.h"
#include "minishell.h"
#include "signals.h"
#include "utils.h"
#include "wildcard.h"

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	int			ret;

	minishell_init(&minishell, ac, av, envp);
	rl_event_hook = &event;
	minishell_main_loop(&minishell);
	ret = minishell.exit_status;
	cleanup_exit(&minishell);
	return (ret);
}
