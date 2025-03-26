/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:44 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 11:10:11 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec.h"
#include "expand.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"
#include "ft_dprintf.h"
#include "built_in.h"

static void	expand_condition(t_ast *node, t_exp_qu *exp_qu)
{
	if (exp_qu->expanded[0])
	{
		node->cmd->cmds[exp_qu->i] = exp_qu->expanded;
		free(exp_qu->temp);
		if (exp_qu->exp == 0)
			exp_qu->i++;
	}
	else
	{
		exp_qu->exp = -1;
		exp_qu->j = exp_qu->i;
		while (node->cmd->cmds[exp_qu->j + 1])
		{
			node->cmd->cmds[exp_qu->j] = node->cmd->cmds[exp_qu->j + 1];
			exp_qu->j++;
		}
		node->cmd->cmds[exp_qu->j] = NULL;
		free(exp_qu->temp);
		free(exp_qu->expanded);
	}
}

static int	qu_check(t_ast *node, t_exp_qu *exp_qu)
{
	exp_qu->final = handle_quotes_exec(node->cmd->cmds[exp_qu->i - 1]);
	if (exp_qu->final == NULL)
		return (1);
	if (exp_qu->final)
	{
		exp_qu->temp = node->cmd->cmds[exp_qu->i - 1];
		node->cmd->cmds[exp_qu->i - 1] = exp_qu->final;
		free(exp_qu->temp);
	}
	if (node->cmd->cmds[exp_qu->i - 1] && exp_qu->i - 1 == 0
		&& node->type == NODE_COMMAND)
	{
		if (is_builtin(node->cmd->cmds[exp_qu->i - 1]) == 1)
			node->type = NODE_BUILTIN;
		if (node->type == NODE_BUILTIN
			&& ft_strcmp(node->cmd->cmds[exp_qu->i - 1], EXPORT) == 0)
			exp_qu->export = 1;
	}
	return (0);
}

static int	expand_quotes_init(t_ast *node, t_exp_qu *exp_qu,
	t_minishell *minishell)
{
	exp_qu->exp = 0;
	exp_qu->quote = 0;
	exp_qu->expanded = expand_env_vars(node->cmd->cmds[exp_qu->i],
			minishell, &exp_qu->exp, &exp_qu->quote);
	if (exp_qu->expanded == NULL)
		return (1);
	if (is_redir_node(node->type) == 1 && !exp_qu->expanded[0])
	{
		free(exp_qu->expanded);
		ft_dprintf(STDERR_FILENO, AMBIGUOUS_ERR, node->cmd->cmds[0]);
		return (1);
	}
	exp_qu->temp = node->cmd->cmds[exp_qu->i];
	expand_condition(node, exp_qu);
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
			data.tmp_cmds = node->cmd->cmds;
			node->cmd->cmds = remake_cmds(node->cmd->cmds, &data.i);
			if (node->cmd->cmds == NULL)
			{
				ft_free_double(data.tmp_cmds);
				return (1);
			}
			free(data.expanded);
			data.i++;
		}
		else if ((data.export == 1 || data.exp == 0 || (data.exp == 1 \
				&& data.quote == 1 && ++data.i)) && qu_check(node, &data) == 1)
			return (1);
	}
	return (0);
}
