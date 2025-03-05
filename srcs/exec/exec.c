#include "minishell.h"

//TODO exit minishell when malloc, pipe, fork error ??

typedef int (* t_handler)(t_ast *node, t_minishell *minishell);

int	handle_and(t_ast *node, t_minishell *minishell)
{
	int	ret;

	ret = exec_minishell(node->left, minishell);
	if (ret == 0)
		ret = exec_minishell(node->right, minishell);
	return (ret);
}

int	handle_or(t_ast *node, t_minishell *minishell)
{
	int	ret;

	ret = exec_minishell(node->left, minishell);
	if (ret != 0)
		ret = exec_minishell(node->right, minishell);
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
	if (len > 1)
		free(str);
	return (ret);
}

void	check_quotes(const char input, bool *in_s_quote, bool *in_d_quote)
{
	if (input == '\'' && !(*in_d_quote))
	{
		if (*in_s_quote)
			*in_s_quote = false; // out of single quotes
		else
			*in_s_quote = true; // enter single quotes
	}
	else if (input == '\"' && !(*in_s_quote))
	{
		if (*in_d_quote)
			*in_d_quote = false; // out of double quotes
		else
			*in_d_quote = true; // enter double quotes
	}
}

char	*handle_quotes_exec(char *input)
{
	char	*result;
	int		len;
	bool	in_s_quote;
	bool	in_d_quote;

	result = NULL;
	len = 0;
	in_s_quote = false;
	in_d_quote = false;
	if (ft_strcmp(input, "\"\"") == 0 || ft_strcmp(input, "''") == 0)
	{
		result = ft_calloc(1, sizeof(char)); // TODO protect
		return (result);
	}
	while ((*input))
	{
		if ((*input == '\'' && !in_d_quote) || (*input == '\"' && !in_s_quote))
			check_quotes(*input, &in_s_quote, &in_d_quote);
		// if we are not in quotes, or in double quotes, or in single quotes
		else if ((in_s_quote && !in_d_quote) || (in_d_quote && !in_s_quote)
			|| (!in_s_quote && !in_d_quote))
		{
			len++;
			result = ft_reallocate(result, *input, len);
			if (!result)
				return (NULL);
		}
		input++;
	}
	return (result);
}

int	exec_minishell(t_ast *node, t_minishell *minishell)
{
	int	ret;
	static t_handler	exec[] = {&handle_or, &handle_and, &handle_cmd,
		&handle_pipe, &handle_redirout, &handle_redirin, &handle_redirappend,
		&handle_heredocin, &handle_builtin};

	if (!node)
		return (0);
	int	i = 0;
	while (node->cmd->cmds[i])
	{
		char *expanded;
		char *temp;
		char *final;
		expanded = expand_env_vars(node->cmd->cmds[i], minishell->envp); //TODO protect
		ft_dprintf(STDERR_FILENO, GREEN"expanded = '%s'\n"RESET, expanded);
		temp = node->cmd->cmds[i];
		if ((node->type == NODE_COMMAND || node->type == NODE_BUILTIN) || expanded[0])
		{
			node->cmd->cmds[i] = expanded;
			free(temp);
		}
		final = handle_quotes_exec(node->cmd->cmds[i]);
		ft_dprintf(STDERR_FILENO, PURPLE"final = %s\n"RESET, final);
		temp = node->cmd->cmds[i];
		node->cmd->cmds[i] = final;
		free(temp);
		if (i == 0)
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
	ret = exec[node->type](node, minishell);
	return (ret);
}
