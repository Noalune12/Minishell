/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:44 by lbuisson          #+#    #+#             */
/*   Updated: 2025/07/24 15:32:08 by gueberso         ###   ########.fr       */
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
#include "wildcard.h"

void	expand_condition(t_ast *node, t_exp_qu *exp_qu)
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

int	qu_check(t_ast *node, t_exp_qu *exp_qu)
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

bool	handle_wildcard_expansion(t_ast *node, t_exp_qu *exp_qu)
{
	char	**new_cmds;
	int		wildcard_count;

	if (!contain_wildcard(node->cmd->cmds[exp_qu->i - 1]))
		return (true);
	wildcard_count = count_wildcard_matches(node->cmd->cmds[exp_qu->i - 1]);
	new_cmds = expand_wildcard_in_cmds(node->cmd->cmds, exp_qu->i - 1);
	if (!new_cmds)
		return (false);
	if (new_cmds != node->cmd->cmds)
	{
		node->cmd->cmds = new_cmds;
		exp_qu->i = exp_qu->i - 1 + wildcard_count;
	}
	return (true);
}

int	check_redirect_ambiguity(t_ast *node, t_exp_qu *exp_qu, \
	char *original_pattern)
{
	if (is_redir_node(node->type) != 1 || exp_qu->i != 0)
		return (0);
	if (exp_qu->expanded[0] && !is_ambiguous_redirect(original_pattern))
		return (0);
	free(exp_qu->expanded);
	if (is_ambiguous_redirect(original_pattern))
		ft_dprintf(STDERR_FILENO, AMBIGUOUS_ERR, original_pattern);
	else
		ft_dprintf(STDERR_FILENO, AMBIGUOUS_ERR, node->cmd->cmds[0]);
	return (1);
}

int	init_expansion_data(t_ast *node, t_exp_qu *exp_qu, \
	t_minishell *minishell, char **original_pattern)
{
	exp_qu->exp = 0;
	exp_qu->quote = 0;
	*original_pattern = ft_strdup(node->cmd->cmds[exp_qu->i]);
	if (!*original_pattern)
		return (1);
	(void) minishell;
	exp_qu->expanded = expand_env_vars(node->cmd->cmds[exp_qu->i],
			minishell, &exp_qu->exp, &exp_qu->quote);
	if (exp_qu->expanded == NULL)
	{
		free(*original_pattern);
		return (1);
	}
	return (0);
}
