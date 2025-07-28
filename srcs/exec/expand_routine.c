/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:31:05 by gueberso          #+#    #+#             */
/*   Updated: 2025/07/24 15:38:54 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec.h"
#include "libft.h"
#include "utils.h"
#include "wildcard.h"

static int	expand_quotes_init(t_ast *node, t_exp_qu *exp_qu, \
	t_minishell *minishell)
{
	char	*original_pattern;

	if (init_expansion_data(node, exp_qu, minishell, &original_pattern) == 1)
		return (1);
	if (check_redirect_ambiguity(node, exp_qu, original_pattern) == 1)
	{
		free(original_pattern);
		return (1);
	}
	free(original_pattern);
	exp_qu->temp = node->cmd->cmds[exp_qu->i];
	expand_condition(node, exp_qu);
	return (0);
}

static int	handle_word_splitting(t_ast *node, t_exp_qu *data)
{
	data->tmp_cmds = node->cmd->cmds;
	node->cmd->cmds = remake_cmds(node->cmd->cmds, &data->i);
	if (node->cmd->cmds == NULL)
	{
		ft_free_double(data->tmp_cmds);
		return (1);
	}
	free(data->expanded);
	data->i++;
	return (0);
}

static int	handle_quote_processing(t_ast *node, t_exp_qu *data)
{
	if (qu_check(node, data) == 1)
		return (1);
	if (handle_wildcard_expansion(node, data) == false)
		return (1);
	return (0);
}

int	expand_quotes_exec(t_ast *node, t_minishell *minishell)
{
	t_exp_qu	data;

	ft_memset(&data, 0, sizeof(t_exp_qu));
	while (node->cmd->cmds[data.i])
	{
		if (expand_quotes_init(node, &data, minishell) == 1)
			return (1);
		if (data.export == 0 && data.exp == 1 && data.quote == 0
			&& node->cmd->cmds[data.i])
		{
			if (handle_word_splitting(node, &data) == 1)
				return (1);
		}
		else if (data.export == 1 || data.exp == 0 || \
			(data.exp == 1 && data.quote == 1))
		{
			if (data.exp == 1 && data.quote == 1)
				data.i++;
			if (handle_quote_processing(node, &data) == 1)
				return (1);
		}
	}
	return (0);
}
