#include "minishell.h"
 //TODO protect

t_cmd	*add_cmd(char *content)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->path = NULL;
	new_cmd->cmds = (char **)malloc(2 * sizeof(char *));
	new_cmd->cmds[0] = ft_strdup(content);
	new_cmd->cmds[1] = NULL;
	return (new_cmd);
}

t_ast *create_ast_tree_node(t_node_type type, char *content, t_ast *parent)
{
	t_ast *node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->cmd = add_cmd(content);
	node->left = NULL;
	node->right = NULL;
	if (parent && !parent->left)
		parent->left = node;
	else if (parent && !parent->right)
		parent->right = node;
	return (node);
}

char	**update_cmd(char **cmds, char *content)
{
	char	**new_cmds;
	size_t	i;

	i = 0;
	while (cmds[i])
		i++;
	new_cmds = (char **)malloc((i+ 2) * sizeof(char *)); //protect
	i = 0;
	while (cmds[i])
	{
		new_cmds[i] = ft_strdup(cmds[i]);
		i++;
	}
	new_cmds[i] = ft_strdup(content);
	new_cmds[i + 1] = NULL;
	ft_free(cmds);
	return(new_cmds);
}

char	**update_heredoc(char **cmds, char *content)
{
	char	**new_cmd;

	new_cmd = (char **)malloc(2 * sizeof(char *));
	new_cmd[0] = ft_strdup(content);
	new_cmd[1] = NULL;
	ft_free(cmds);
	return (new_cmd);
}

int	is_redir_node(t_node_type type)
{
	if (type == NODE_REDIR_OUT
	|| type == NODE_REDIR_IN
	|| type == NODE_APPEND
	|| type == NODE_HEREDOC)
		return (1);
	return (0);
}

t_ast	*create_command(t_token **token)
{
	t_token	*token_redir;
	t_ast	*node_cmd = NULL;
	t_ast	*node_redir = NULL;
	t_ast	*node_heredoc = NULL;
	t_ast	*node = NULL;

	while ((*token))
	{
		if (is_redir_node((*token)->type))
		{
			token_redir = *token;
			(*token) = (*token)->next;
			if (token_redir->type != NODE_HEREDOC)
				node_redir = create_ast_tree_node(token_redir->type, (*token)->content, node_redir);
			else
			{
				if (node_heredoc)
					node_heredoc->cmd->cmds = update_heredoc(node_heredoc->cmd->cmds, (*token)->content);
				else
				{
					node_heredoc = create_ast_tree_node(token_redir->type, (*token)->content, node_redir);
					node_redir = node_heredoc;
				}
			}
			if (!node)
				node = node_redir;
		}
		else
		{
			if (node_cmd)
				node_cmd->cmd->cmds = update_cmd(node_cmd->cmd->cmds, (*token)->content);
			else
				node_cmd = create_ast_tree_node(NODE_COMMAND, (*token)->content, NULL);
		}
		if ((*token)->next && ((*token)->next->type == NODE_PIPE || (*token)->next->type == NODE_AND || (*token)->next->type == NODE_OR || (*token)->next->type == NODE_CLOSE_PAR))
			break ;
		(*token) = (*token)->next;
	}
	if (!node)
		node = node_cmd;
	else if (node_redir)
		node_redir->left = node_cmd;
	return (node);
}

t_ast	*create_operator(t_token **token)
{
	t_ast	*node;

	node = create_ast_tree_node((*token)->type, (*token)->content, NULL);
	return (node);
}

t_ast *add_up(t_ast *root, t_ast *node)
{
	node->left = root;
	return (node);
}

t_ast *add_to_rightmost(t_ast *root, t_ast *node)
{
	t_ast *temp;

	temp = root;
	if (!root)
		return (node);
	while (temp->right)
		temp = temp->right;
	temp->right = node;
	return (root);
}

t_ast *add_to_left(t_ast *root, t_ast *node)
{
	t_ast *temp;

	temp = root;
	if (!root)
		return (node);
	while (temp->left)
		temp = temp->left;
	temp->left = node;
	return (root);
}

t_ast *add_down_right(t_ast *root, t_ast *node) //or up if needed
{
	t_ast	*temp;

	if (node->type == NODE_COMMAND || is_redir_node(node->type))
		return (add_to_rightmost(root, node));
	if ((root->type == NODE_OR || root->type == NODE_AND) && node->type == NODE_PIPE)
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

t_ast	*add_to_tree(t_ast *root, t_ast *node)
{
	if (!root)
		return (node);
	if (root->type == NODE_COMMAND || is_redir_node(root->type))
		return (add_up(root, node));
	if (root->type == NODE_PIPE || root->type == NODE_AND || root->type == NODE_OR)
	{
		if (node->type == NODE_AND || node->type == NODE_OR)
			return (add_up(root, node));
		return (add_down_right(root, node));
	}
	return (root);
}

t_ast	*make_subast(t_token **token, t_ast *root, int *par)
{
	t_ast	*sub_ast;

	sub_ast = NULL;
	while ((*token)->type != NODE_CLOSE_PAR)
	{
		if ((*token)->type == NODE_COMMAND || is_redir_node((*token)->type))
			sub_ast = add_to_tree(sub_ast, create_command(token));
		else if ((*token)->type == NODE_PIPE || (*token)->type == NODE_OR || (*token)->type == NODE_AND)
			sub_ast = add_to_tree(sub_ast, create_operator(token));
		else if ((*token)->type == NODE_OPEN_PAR)
		{
			*token = (*token)->next;
			sub_ast = make_subast(token, sub_ast, par);
		}
		*token = (*token)->next;
	}
	*par = 1;
	if ((*token)->next && is_redir_node((*token)->next->type))
	{
		(*token) = (*token)->next;
		sub_ast = add_to_left(create_command(token), sub_ast);
		(*par) = 0;
	}
	if (!root)
		root = sub_ast;
	else
		add_to_rightmost(root, sub_ast);
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
			root = add_to_tree(root, create_command(&temp));
		else if (temp->type == NODE_PIPE || temp->type == NODE_OR || temp->type == NODE_AND)
			root = add_to_tree(root, create_operator(&temp));
		else if (temp->type == NODE_OPEN_PAR)
		{
			temp = temp->next;
			root = make_subast(&temp, root, &par);
		}
		if (!temp)
			break ;
		if (par == 0)
			temp = temp->next;
	}
	return (root);
}
