#include "types.h"
#include "ast.h"
#include "minishell.h"

static t_ast	*create_operator(t_token **token, t_ast *root, t_ast *sub_ast)
{
	t_ast	*node = NULL;

	node = create_ast_tree_node((*token)->type, (*token)->content, 0, NULL);
	if (!node)
		return (error_handling_ast(root, sub_ast));
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

static t_ast	*make_subast(t_token **token, t_ast *root, int *par)
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

static void create_node(t_ast **root, t_token **temp, int *par)
{
	*par = 0;
	if ((*temp)->type == NODE_COMMAND || is_redir_node((*temp)->type))
		*root = add_to_ast(*root, create_branch(temp, *root, NULL));
	else if (is_operator_node((*temp)->type))
		*root = add_to_ast(*root, create_operator(temp, *root, NULL));
	else if ((*temp)->type == NODE_OPEN_PAR)
		*root = make_subast(temp, *root, par);
}

void	build_ast(t_minishell *ms)
{
	t_token	*temp;
	t_ast	*root;
	int		par;

	if (ms->exec_status == false)
		return ;
	temp = ms->token;
	root = NULL;
	while (temp)
	{
		create_node(&root, &temp, &par);
		if (!root)
		{
			ms->ast_node = root;
			ms->exec_status = false;
			ms->exit_status = 1;
			return ;
		}
		if (!temp)
			break ;
		if (par == 0)
			temp = temp->next;
	}
	ms->ast_node = root;
}
