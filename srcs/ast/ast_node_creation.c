#include "minishell.h"

static t_cmd	*add_cmd(char *content)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->path = NULL;
	new_cmd->cmds = (char **)malloc(2 * sizeof(char *));
	if (new_cmd->cmds == NULL)
	{
		free(new_cmd);
		return (NULL);
	}
	new_cmd->cmds[0] = ft_strdup(content);
	if (new_cmd->cmds[0] == NULL)
	{
		free(new_cmd->cmds);
		free(new_cmd);
		return (NULL);
	}
	new_cmd->cmds[1] = NULL;
	return (new_cmd);
}

t_ast	*create_ast_tree_node(t_node_type type, char *content,
	bool expand, t_ast *parent)
{
	t_ast	*node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->cmd = add_cmd(content);
	if (node->cmd == NULL)
	{
		free(node);
		return (NULL);
	}
	if (type == NODE_HEREDOC)
		node->cmd->to_expand = expand;
	else
		node->cmd->to_expand = false;
	node->left = NULL;
	node->right = NULL;
	if (parent && !parent->left)
		parent->left = node;
	else if (parent && !parent->right)
		parent->right = node;
	return (node);
}
