/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:56 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 09:21:59 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "ast.h"
#include "exec.h"
#include "minishell.h"

int	handle_or(t_ast *node, t_minishell *minishell)
{
	int	ret;

	ret = exec_minishell(node->left, minishell);
	minishell->exit_status = ret;
	if (ret != 0 && g_signal_received != SIGINT)
	{
		g_signal_received = 0;
		ret = exec_minishell(node->right, minishell);
	}
	return (ret);
}
