#include "minishell.h"

t_ast	*add_up(t_ast *root, t_ast *node)
{
	node->left = root;
	return (node);
}

t_ast	*add_to_rightmost(t_ast *root, t_ast *node)
{
	t_ast	*temp;

	temp = root;
	if (!root)
		return (node);
	while (temp->right)
		temp = temp->right;
	temp->right = node;
	return (root);
}

t_ast	*add_to_left(t_ast *root, t_ast *node)
{
	t_ast	*temp;

	temp = root;
	if (!root)
		return (node);
	while (temp->left)
		temp = temp->left;
	temp->left = node;
	return (root);
}

t_ast	*add_down_right(t_ast *root, t_ast *node) //or up if needed
{
	t_ast	*temp;

	if (node->type == NODE_COMMAND || is_redir_node(node->type))
		return (add_to_rightmost(root, node));
	if ((root->type == NODE_OR || root->type == NODE_AND)
		&& node->type == NODE_PIPE)
	{
		temp = root->right;
		root->right = node;
		node->left = temp;
		return (root);
	}
	temp = root;
	root = node;
	root->left = temp;
	return (root);
}

t_ast	*add_to_ast(t_ast *root, t_ast *node)
{
	if (!node)
		return (NULL);
	if (!root)
		return (node);
	if (root->type == NODE_COMMAND || is_redir_node(root->type))
		return (add_up(root, node));
	if (is_operator_node(root->type))
	{
		if (node->type == NODE_AND || node->type == NODE_OR)
			return (add_up(root, node));
		return (add_down_right(root, node));
	}
	return (root);
}
