/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:27 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 13:01:42 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "ast.h"
#include "exec.h"
#include "minishell.h"

int	handle_and(t_ast *node, t_minishell *minishell)
{
	int	ret;

	ret = exec_minishell(node->left, minishell);
	minishell->exit_status = ret;
	if (ret == 0 && g_signal_received != SIGINT)
	{
		g_signal_received = 0;
		ret = exec_minishell(node->right, minishell);
	}
	return (ret);
}
