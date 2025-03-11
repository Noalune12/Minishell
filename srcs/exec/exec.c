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

//TODO see if done in parsing part ?

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
		printf("Malloc failed");
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

char **remove_null_strings(char **strs, int nb_cmd)
{
	int count = 0;
	int i = 0;
	int j = 0;
	char **new_strs;

	while (nb_cmd > 0)
	{
		if (strs[i] != NULL)
			count++;
		nb_cmd--;
		i++;
	}
	new_strs = (char **)malloc((count + 1) * sizeof(char *));
	if (!new_strs)
		return NULL;
	i = 0;
	while (j < count)
	{
		if (strs[i] != NULL)
			new_strs[j++] = strs[i];
		else
			free(strs[i]);
		i++;
	}
	new_strs[j] = NULL;
	free(strs);
	return (new_strs);
}

int	exec_minishell(t_ast *node, t_minishell *minishell)
{
	int	ret;
	static t_handler	exec[] = {&handle_cmd, &handle_pipe, &handle_or, &handle_and,
		&handle_redirin, &handle_redirout, &handle_heredocin,
		&handle_redirappend, 0, 0, &handle_builtin};

	if (!node || minishell->exec_status == false)
		return (0);
	if (node->type == NODE_HEREDOC)
		return handle_heredocin(node, minishell);
	int i = 0;
	while (node->cmd->cmds[i])
	{
		char *expanded;
		char *temp;
		char *final;
		expanded = expand_env_vars(node->cmd->cmds[i], minishell->envp, minishell); // TODO handle $? if command
		ft_dprintf(STDERR_FILENO, GREEN"expanded = '%s'\n"RESET, expanded); // delete
		temp = node->cmd->cmds[i];
		if ((node->type == NODE_COMMAND || node->type == NODE_BUILTIN))
		{
			if (expanded[0])
			{
				node->cmd->cmds[i] = expanded;
				free(temp);
			}
			else
			{
				node->cmd->cmds[i] = NULL;
				free(temp);
				free(expanded);
			}
		}
		else
			free(expanded);
		final = handle_quotes_exec(node->cmd->cmds[i]);
		ft_dprintf(STDERR_FILENO, PURPLE"final = %s\n"RESET, final); // delete
		if (final)
		{
			temp = node->cmd->cmds[i];
			node->cmd->cmds[i] = final;
			free(temp);
		}
		if (i == 0 && node->type == NODE_COMMAND)
		{
			if (ft_strcmp(node->cmd->cmds[i], "echo\0") == 0
				|| ft_strcmp(node->cmd->cmds[i], "cd\0") == 0
				|| ft_strcmp(node->cmd->cmds[i], "pwd\0") == 0
				|| ft_strcmp(node->cmd->cmds[i], "export\0") == 0
				|| ft_strcmp(node->cmd->cmds[i], "unset\0") == 0
				|| ft_strcmp(node->cmd->cmds[i], "env\0") == 0
				|| ft_strcmp(node->cmd->cmds[i], "exit\0") == 0)
				node->type = NODE_BUILTIN;
		}
		i++;
	}
	node->cmd->cmds = remove_null_strings(node->cmd->cmds, i);
	ret = exec[node->type](node, minishell);
	return (ret);
}
