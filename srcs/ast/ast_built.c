#include "minishell.h"

t_ast	*create_operator(t_token **token, t_ast *root, t_ast *sub_ast)
{
	t_ast	*node;

	node = create_ast_tree_node((*token)->type, (*token)->content, 0, NULL);
	if (!node)
		return (error_handling_ast(root, sub_ast, "Malloc failed\n"));
	return (node);
}

static void	place_subast(t_token **token, t_ast **root,
	t_ast **sub_ast, int *par)
{
	*par = 1;
	if ((*token)->next && is_redir_node((*token)->next->type))
	{
		(*token) = (*token)->next;
		*sub_ast = add_to_left(create_branch(token, *root, *sub_ast),
				*sub_ast);
		(*par) = 0;
	}
	if (root && !(*root))
		*root = *sub_ast;
	else
		add_to_rightmost(*root, *sub_ast);
}

t_ast	*make_subast(t_token **token, t_ast *root, int *par)
{
	t_ast	*sub_ast;

	sub_ast = NULL;
	*token = (*token)->next;
	while ((*token)->type != NODE_CLOSE_PAR)
	{
		if ((*token)->type == NODE_COMMAND || is_redir_node((*token)->type))
			sub_ast = add_to_ast(sub_ast, create_branch(token, root, sub_ast));
		else if (is_operator_node((*token)->type))
			sub_ast = add_to_ast(sub_ast,
					create_operator(token, root, sub_ast));
		else if ((*token)->type == NODE_OPEN_PAR)
			sub_ast = make_subast(token, sub_ast, par);
		if (!sub_ast)
			return (NULL);
		*token = (*token)->next;
	}
	place_subast(token, &root, &sub_ast, par);
	return (root);
}

t_ast	*build_ast(t_token **token, bool *exec_status)
{
	t_token	*temp;
	t_ast	*root;
	int		par;

	if (*exec_status == false)
		return (NULL);
	temp = *token;
	root = NULL;
	while (temp)
	{
		par = 0;
		if (temp->type == NODE_COMMAND || is_redir_node(temp->type))
			root = add_to_ast(root, create_branch(&temp, root, NULL));
		else if (is_operator_node(temp->type))
			root = add_to_ast(root, create_operator(&temp, root, NULL));
		else if (temp->type == NODE_OPEN_PAR)
			root = make_subast(&temp, root, &par);
		if (!root)
			return (NULL);
		if (!temp)
			break ;
		if (par == 0)
			temp = temp->next;
	}
	return (root);
}
