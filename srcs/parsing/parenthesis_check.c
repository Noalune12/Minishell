/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:34 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 13:34:11 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "ft_dprintf.h"
#include "minishell.h"

int	check_parentheses_tokens(t_token *current, t_token *next,
								t_minishell *minishell)
{
	if (current->type == NODE_CLOSE_PAR && next->type == NODE_COMMAND)
	{
		ft_dprintf(STDERR_FILENO, STR_SYNTAX, next->content);
		minishell->exit_status = 2;
		minishell->exec_status = false;
		return (-1);
	}
	if (current->type == NODE_COMMAND && next->type == NODE_OPEN_PAR)
	{
		ft_dprintf(STDERR_FILENO, STR_SYNTAX, next->content);
		minishell->exit_status = 2;
		minishell->exec_status = false;
		return (-1);
	}
	return (0);
}

int	check_unbalanced_parenthesis(t_token *token, int *paren_count,
									t_minishell *minishell)
{
	if (token->type == NODE_OPEN_PAR)
		(*paren_count)++;
	else if (token->type == NODE_CLOSE_PAR)
	{
		(*paren_count)--;
		if (*paren_count < 0)
		{
			ft_dprintf(STDERR_FILENO, STR_SYNTAX, token->content);
			minishell->exit_status = 2;
			minishell->exec_status = false;
			return (-1);
		}
	}
	return (0);
}
