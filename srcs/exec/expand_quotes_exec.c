#include "minishell.h"

static int	fill_new_cmds(char **cmds, int *index, char **new_cmd, char **ret)
{
	int		i;
	int		k;
	int		j;

	i = -1;
	while (++i < *index)
		ret[i] = cmds[i];
	j = -1;
	while (new_cmd[++j])
	{
		ret[*index] = new_cmd[j];
		(*index)++;
	}
	k = *index;
	i++;
	while (cmds[i])
	{
		ret[k] = cmds[i];
		i++;
		k++;
	}
	ret[k] = NULL;
	return (0);
}

static char	**remake_cmds(char **cmds, int *index)
{
	char	**new_cmd;
	int		cmds_len;
	int		new_cmd_len;
	char	**ret;

	cmds_len = 0;
	new_cmd_len = 0;
	new_cmd = ft_split(cmds[*index], ' '); // TODO protect
	if (!new_cmd)
		return (NULL);
	while (cmds[cmds_len])
		cmds_len++;
	while (new_cmd[new_cmd_len])
		new_cmd_len++;
	ret = malloc((cmds_len + new_cmd_len) * sizeof(char *)); // TODO protect
	if (!ret)
	{
		free(new_cmd);
		return (NULL);
	}
	fill_new_cmds(cmds, index, new_cmd, ret);
	(*index)--;
	free(cmds);
	free(new_cmd);
	return (ret);
}

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

int	expand_quotes_exec(t_ast *node, t_minishell *minishell)
{
	t_exp_qu	exp_qu;

	ft_memset(&exp_qu, 0, sizeof(t_exp_qu));
	while (node->cmd->cmds[exp_qu.i])
	{
		exp_qu.exp = 0;
		exp_qu.quote = 0;
		exp_qu.expanded = expand_env_vars(node->cmd->cmds[exp_qu.i],
				minishell, &exp_qu.exp, &exp_qu.quote); // TODO protect
		if (!exp_qu.expanded)
			return(1);
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
		else if (exp_qu.exp == 0 && quote_condition(node, &exp_qu) == 1)
				return (1); // TODO protect
	}
	return (0);
}
