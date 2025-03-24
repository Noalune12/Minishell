#include "minishell.h"
#include "exec.h"

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

static int	quote_condition(t_ast *node, t_exp_qu *exp_qu)
{
	exp_qu->final = handle_quotes_exec(node->cmd->cmds[exp_qu->i - 1]); // TODO protect
	if (!exp_qu->final)
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
	}
	return (0);
}

static void	expand_quotes_init(t_ast *node, t_exp_qu *exp_qu,
	t_minishell *minishell)
{
	exp_qu->exp = 0;
	exp_qu->quote = 0;
	exp_qu->expanded = expand_env_vars(node->cmd->cmds[exp_qu->i],
			minishell, &exp_qu->exp, &exp_qu->quote); // TODO protect
}

int	expand_quotes_exec(t_ast *node, t_minishell *minishell)
{
	t_exp_qu	exp_qu;

	ft_memset(&exp_qu, 0, sizeof(t_exp_qu));
	while (node->cmd->cmds[exp_qu.i])
	{
		expand_quotes_init(node, &exp_qu, minishell);
		if (!exp_qu.expanded)
			return (1);
		exp_qu.temp = node->cmd->cmds[exp_qu.i];
		expand_condition(node, &exp_qu);
		if (exp_qu.exp == 1 && exp_qu.quote == 0 && node->cmd->cmds[exp_qu.i])
		{
			node->cmd->cmds = remake_cmds(node->cmd->cmds, &exp_qu.i); // TODO protect
			free(exp_qu.expanded);
			if (!node->cmd->cmds)
				return (1);
			exp_qu.i++;
		}
		else if ((exp_qu.exp == 0 || (exp_qu.exp == 1 && exp_qu.quote == 1
				&& ++exp_qu.i)) && quote_condition(node, &exp_qu) == 1) // TODO export A='"' export B="a b c $A" echo $B
				return (1); // TODO protect
	}
	return (0);
}
