#include "minishell.h"

//TODO exit minishell when malloc, pipe, fork error ??

typedef int (* t_handler)(t_ast *node, t_minishell *minishell);

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

char	*ft_reallocate(char *str, char c, int len)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * (len + 2));
	if (!ret)
	{
		if (len > 1)
			free(str);
		ft_dprintf(STDERR_FILENO, "Malloc failed");
		return (NULL);
	}
	while (len > 1 && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	if (len > 0)
		free(str);
	return (ret);
}

void	init_data(t_quotes *data, char *input)
{
	data->in_dquotes = false;
	data->in_squotes = false;
	data->original = input;
	data->len = 0;
	data->result = ft_calloc(1, sizeof(char));
}

int	handle_quotes_main_loop(t_quotes *data, char *input)
{
	while (*input)
	{
		if ((*input == '\'' && !data->in_dquotes) || (*input == '\"' && !data->in_squotes))
		{
			if (*input == '\'')
				data->in_squotes = !data->in_squotes;
			else if (*input == '\"')
				data->in_dquotes = !data->in_dquotes;
		}
		else
		{
			data->len++;
			data->result = ft_reallocate(data->result, *input, data->len);
			if (!data->result)
				return (-1);
		}
		input++;
	}
	return (0);
}

char *handle_quotes_exec(char *input)
{
	t_quotes	data;

	if (!input)
		return (NULL);
	init_data(&data, input);
	if (!data.result)
		return (NULL);
	if (ft_strcmp(input, "\"\"") == 0 || ft_strcmp(input, "''") == 0)
		return (data.result);
	if (handle_quotes_main_loop(&data, input) == -1)
		return (NULL);
	if (data.in_squotes || data.in_dquotes)
	{
		free(data.result);
		return (ft_strdup(data.original));
	}
	return (data.result);
}

char	**remake_cmds(char **cmds, int *index)
{
	char	**new_cmd;
	int		cmds_len = 0;
	int		new_cmd_len = 0;
	char	**ret;
	int		i;

	new_cmd = ft_split(cmds[*index], ' '); // TODO protect
	// for (int i = 0; new_cmd[i]; i++)
	// 	ft_dprintf(STDERR_FILENO, "new cmd %d = %s\n",  i, new_cmd[i]);
	while (cmds[cmds_len])
		cmds_len++;
	while (new_cmd[new_cmd_len])
		new_cmd_len++;
	ret = malloc((cmds_len + new_cmd_len) * sizeof(char *)); // TODO protect
	i = 0;
	while (i < *index)
	{
		ret[i] = cmds[i];
		i++;
	}
	int j = -1;
	while (new_cmd[++j])
	{
		ret[*index] = new_cmd[j];
		(*index)++;
	}
	int k = *index;
	i++;
	while (cmds[i])
	{
		ret[k] = cmds[i];
		i++;
		k++;
	}
	ret[k] = NULL;
	(*index)--;
	free(cmds);
	free(new_cmd);
	return (ret);
}

int	exec_minishell(t_ast *node, t_minishell *minishell)
{
	char *expanded;
	int	ret;
	static t_handler	exec[] = {&handle_cmd, &handle_pipe, &handle_or, &handle_and,
		&handle_redirin, &handle_redirout, &handle_heredocin,
		&handle_redirappend, 0, 0, &handle_builtin};

	if (!node || minishell->exec_status == false)
		return (0);
	if (node->type == NODE_HEREDOC)
		return handle_heredocin(node, minishell);
	int i = 0;
	int j = 0;
	while (node->cmd->cmds[i])
	{

		char *temp;
		int	exp = 0;
		int	quote = 0;
		expanded = expand_env_vars(node->cmd->cmds[i], minishell->envp, minishell, &exp, &quote);
		// ft_dprintf(STDERR_FILENO, GREEN"expanded = '%s'\n"RESET, expanded); // delete
		temp = node->cmd->cmds[i];
		if (expanded[0])
		{
			node->cmd->cmds[i] = expanded;
			free(temp);
			if (exp == 0)
				i++;
		}
		else
		{
			exp = -1;
			j = i;
			while (node->cmd->cmds[j + 1])
			{
				node->cmd->cmds[j] = node->cmd->cmds[j + 1];
				j++;
			}
			node->cmd->cmds[j] = NULL;
			free(temp);
			free(expanded);
		}
		if (exp == 1 && quote == 0 && node->cmd->cmds[i])
		{
			node->cmd->cmds = remake_cmds(node->cmd->cmds, &i);
			free(expanded);
			i++;
		}
		else if (exp == 0)
		{
			char *temp;
			char *final;
			final = handle_quotes_exec(node->cmd->cmds[i - 1]);
			// ft_dprintf(STDERR_FILENO, PURPLE"final = %s\n"RESET, final); // delete
			if (final)
			{
				temp = node->cmd->cmds[i - 1];
				node->cmd->cmds[i - 1] = final;
				free(temp);
			}
			if (node->cmd->cmds[i - 1] && i - 1 == 0 && node->type == NODE_COMMAND)
			{
				if (is_builtin(node->cmd->cmds[i - 1]) == 1)
					node->type = NODE_BUILTIN;
			}
		}
	}
	if (!node->cmd->cmds[0])
		return (0);
	ret = exec[node->type](node, minishell);
	return (ret);
}
