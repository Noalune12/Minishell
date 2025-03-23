#include "minishell.h"

static char	**update_cmd_content(char **cmds, char **new_cmds, char *content)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		new_cmds[i] = ft_strdup(cmds[i]);
		if (!new_cmds[i])
		{
			ft_free(cmds);
			free_tab(new_cmds, i);
			return (NULL);
		}
		i++;
	}
	new_cmds[i] = ft_strdup(content);
	if (!new_cmds[i])
	{
		ft_free(cmds);
		free_tab(new_cmds, i);
		return (NULL);
	}
	new_cmds[i + 1] = NULL;
	return (new_cmds);
}

static char	**update_cmd(char **cmds, char *content)
{
	char	**new_cmds;
	int		i;

	i = 0;
	while (cmds[i])
		i++;
	new_cmds = (char **)malloc((i + 2) * sizeof(char *));
	if (!new_cmds)
	{
		ft_free(cmds);
		return (NULL);
	}
	if (update_cmd_content(cmds, new_cmds, content) == NULL)
		return (NULL);
	ft_free(cmds);
	return (new_cmds);
}

static int	create_redir(t_token **token, t_branch *branch,
	t_ast *root, t_ast *sub_ast)
{
	branch->token_redir = *token;
	(*token) = (*token)->next;
	if (is_redir_node_not_heredoc(branch->token_redir->type)
		|| (branch->token_redir->type == NODE_HEREDOC
			&& !still_heredoc_left(*token)))
	{
		branch->node_redir = create_ast_tree_node(branch->token_redir->type,
				(*token)->content, (*token)->to_expand, branch->node_redir);
		if (!(branch->node_redir))
		{
			free_ast(branch->node);
			free_ast(branch->node_cmd);
			error_handling_ast(root, sub_ast, "Malloc failed\n");
			return (0);
		}
	}
	if (!(branch->node))
		branch->node = branch->node_redir;
	return (1);
}

static t_ast	*create_cmd(t_token **token, t_branch *branch,
	t_ast *root, t_ast *sub_ast)
{
	if (branch->node_cmd)
	{
		branch->node_cmd->cmd->cmds = update_cmd(branch->node_cmd->cmd->cmds,
				(*token)->content);
		if (!branch->node_cmd->cmd->cmds)
		{
			free_ast(branch->node);
			free_ast(branch->node_cmd);
			return (error_handling_ast(root, sub_ast, "Malloc failed\n"));
		}
	}
	else
	{
		branch->node_cmd = create_ast_tree_node(NODE_COMMAND,
				(*token)->content, 0, NULL);
		if (!branch->node_cmd)
		{
			free_ast(branch->node);
			free_ast(branch->node_cmd);
			return (error_handling_ast(root, sub_ast, "Malloc failed\n"));
		}
	}
	return (branch->node_cmd);
}

t_ast	*create_branch(t_token **token, t_ast *root, t_ast *sub_ast)
{
	t_branch	branch;

	ft_memset(&branch, 0, sizeof(t_branch));
	while ((*token))
	{
		if (is_redir_node((*token)->type))
		{
			if (create_redir(token, &branch, root, sub_ast) == 0)
				return (NULL);
		}
		else if (create_cmd(token, &branch, root, sub_ast) == NULL)
			return (NULL);
		if ((*token)->next && ((is_operator_node((*token)->next->type) \
				|| (*token)->next->type == NODE_CLOSE_PAR)))
			break ;
		(*token) = (*token)->next;
	}
	if (!branch.node)
		branch.node = branch.node_cmd;
	else if (branch.node_redir)
		branch.node_redir->left = branch.node_cmd;
	return (branch.node);
}
