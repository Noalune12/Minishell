#include "minishell.h"

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

t_ast *add_child(t_ast *parent, t_ast *child)
{
	if (!parent->right)
		parent->right = child;
	else
		parent->left = child;
	return (parent);
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

void ft_swap(t_ast *a, t_ast *b)
{
	t_ast	temp;

	temp = *a;
	*a = *b;
	*b = temp;
	b->left = NULL;
	a->left = b;
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

t_ast	*create_command(t_token **token, t_ast **head, t_ast **root)
{
	t_token	*token_redir;
	t_ast	*node_cmd = NULL;
	t_ast	*node_redir = NULL;
	t_ast	*node_heredoc = NULL;
	t_ast	*node = NULL;

	while ((*token) && (*token)->type != NODE_PIPE)
	{
		if ((*token)->type == NODE_REDIR_OUT
		|| (*token)->type == NODE_REDIR_IN
		|| (*token)->type == NODE_APPEND
		|| (*token)->type == NODE_HEREDOC)
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
		if ((*token)->next && ((*token)->next->type == NODE_PIPE || (*token)->next->type == NODE_AND || (*token)->next->type == NODE_OR))
			break ;
		(*token) = (*token)->next;
	}
	if (!node)
		node = node_cmd;
	else if (node_redir)
		node_redir->left = node_cmd;
	if (head && *head && !(*head)->right)
		(*head)->right = node;
	else if (root && *root && !(*root)->right)
		(*root)->right = node;
	return (node);
}

t_ast	*create_pipe(t_token **token, t_ast **left, t_ast **head, t_ast **root)
{
	t_ast	*node_pipe;

	node_pipe = create_ast_tree_node(NODE_PIPE, (*token)->content, NULL);
	if (root && *root)
	{
		node_pipe->left = (*root)->right;
		(*root)->right = node_pipe;
	}
	else if (head && *head)
		node_pipe->left = *head;
	if (left && *left && !node_pipe->left)
		node_pipe->left = *left;
	return (node_pipe);
}

t_ast	*create_or_and(t_token **token, t_ast **left, t_ast **head, t_ast **root)
{
	t_ast	*node_and_or;

	node_and_or = create_ast_tree_node((*token)->type, (*token)->content, NULL);
	if (root && *root)
		node_and_or->left = *root;
	else if (head && *head)
		node_and_or->left = *head;
	else if (left && *left && !node_and_or->left)
		node_and_or->left = *left;
	if (head && *head)
		*head = NULL;
	return (node_and_or);
}

t_ast	*build_ast(t_token **token)
{
	t_token	*temp = *token;
	t_ast	*root = NULL;
	t_ast	*head_pipe = NULL;
	t_ast	*left = NULL;

	while (temp)
	{
		if (temp->type == NODE_OR || temp->type == NODE_AND)
			root = create_or_and(&temp, &left, &head_pipe, &root);
		else if (temp->type == NODE_PIPE)
			head_pipe = create_pipe(&temp, &left, &head_pipe, &root);
		else
		{
			if (!left)
				left = create_command(&temp, &head_pipe, &root);
			else
			{
				create_command(&temp, &head_pipe, &root);
				if (root)
					left = NULL;
			}
		}
		if (!temp)
			break ;
		temp = temp->next;
	}
	if (!root)
		root = head_pipe;
	if (!root)
		root = left;
	return (root);
}

// void create_ast(t_minishell *minishell)
// {
// 	t_token	*temp = minishell->token;
// 	t_ast	*command_node = NULL;
// 	t_ast	*prev_cmd = NULL;
// 	t_ast	*current = NULL;
// 	t_ast	*head = NULL;
// 	t_ast	*prev_and_or = NULL;
// 	bool	left = true;
// 	t_ast *prev_pipe = NULL;
// 	t_ast *first_file = NULL;
// 	t_ast *prev_file = NULL;
// 	t_ast *parenthesis = NULL;
// 	t_ast *last_pipe = NULL;
// 	// t_ast *last_or_and = NULL;

// 	while (temp)
// 	{
// 		if (temp->type == NODE_OPEN_PAR)
// 		{
// 			// check if is still in parenthesis to recall function
// 			temp = temp->next;
// 			parenthesis = create_parenthesis(temp);
// 			// print_ast(parenthesis, 0);
// 			while (temp->type == NODE_CLOSE_PAR)
// 				temp = temp ->next;
// 			// printf("now temp = %s\n", temp->content);
// 			// printf("current = %s\n", current->cmd->cmds[0]);
// 			// printf("\n------current----------\n");
// 			// print_ast(current, 0);
// 			// printf("\n------last pipe----------\n");
// 			// print_ast(last_pipe, 0);
// 			if (last_pipe && !prev_and_or)
// 			{
// 				current->left = last_pipe->right;
// 				last_pipe->right = current;
// 				current->right = parenthesis;
// 				head = last_pipe;
// 			}
// 			else if (last_pipe && prev_and_or)
// 			{
// 				current->left = last_pipe->right;
// 				last_pipe->right = current;
// 				current->right = parenthesis;
// 			}
// 			else if (!last_pipe && prev_and_or)
// 			{
// 				prev_and_or->right = parenthesis;
// 				last_pipe = parenthesis;
// 				prev_pipe = parenthesis;
// 			}
// 			else
// 				head = parenthesis;
// 			// printf("\n------ast----------\n");
// 			// print_ast(head, 0);
// 		}
// 		else if (temp->type == NODE_AND
// 			|| temp->type == NODE_OR)
// 		{
// 			if (temp->type == NODE_AND)
// 				current = create_ast_tree_node(NODE_AND, temp->content);
// 			else
// 				current = create_ast_tree_node(NODE_OR, temp->content);
// 			if (head)
// 				add_child(current, head);
// 			prev_and_or = current;
// 			head = current;
// 			prev_cmd = NULL;
// 			first_file = NULL;
// 			prev_pipe = NULL;
// 			left = false;
// 			prev_file = NULL;
// 			last_pipe = NULL;
// 		}
// 		else if (temp->type == NODE_PIPE)
// 		{
// 			current = create_ast_tree_node(NODE_PIPE, temp->content);
// 			if (prev_cmd && left == false && !prev_pipe && !first_file)
// 				current->left = prev_cmd;
// 			else if (left == false && !prev_pipe && first_file)
// 				current->left = first_file;
// 			if (prev_pipe)
// 			{
// 				current->left = prev_pipe;
// 				prev_and_or->right = current;
// 			}
// 			if (prev_and_or)
// 			{
// 				add_child(prev_and_or, current);
// 				prev_pipe = current;
// 			}
// 			else if (head)
// 				add_child(current, head);
// 			if (!prev_and_or)
// 				head = current;
// 			prev_cmd = NULL;
// 			first_file = NULL;
// 			prev_file = NULL;
// 			if (temp->type == NODE_OPEN_PAR)
// 				last_pipe = current;
// 		}
// 		else if (temp->type == NODE_REDIR_OUT
// 		|| temp->type == NODE_REDIR_IN
// 		|| temp->type == NODE_APPEND
// 		|| temp->type == NODE_HEREDOC)
// 		{
// 			if (temp->type == NODE_REDIR_OUT)
// 			{
// 				temp = temp->next;
// 				current = create_ast_tree_node(NODE_REDIR_OUT, temp->content);
// 			}
// 			else if (temp->type == NODE_REDIR_IN)
// 			{
// 				temp = temp->next;
// 				current = create_ast_tree_node(NODE_REDIR_IN, temp->content);
// 			}
// 			else if (temp->type == NODE_APPEND)
// 			{
// 				temp = temp->next;
// 				current = create_ast_tree_node(NODE_APPEND, temp->content);
// 			}
// 			else
// 			{
// 				while (temp->next && (temp->next->type == NODE_COMMAND || temp->next->type == NODE_HEREDOC))
// 					temp = temp->next;
// 				current = create_ast_tree_node(NODE_HEREDOC, temp->content);
// 			}
// 			if (head && prev_cmd)
// 			{
// 				add_child(prev_cmd, current);
// 				ft_swap(prev_cmd, current);
// 				if (!first_file)
// 					first_file = prev_cmd;
// 				prev_cmd = prev_cmd->left;
// 			}
// 			else if (!head)
// 				head = current;
// 			else if (prev_pipe && !prev_cmd)
// 			{
// 				if (prev_file)
// 					add_child(prev_file, current);
// 				else
// 					add_child(prev_pipe, current);
// 				if (!first_file)
// 					first_file = current;
// 			}
// 			else if (!prev_cmd)
// 			{
// 				if (prev_file)
// 					add_child(prev_file, current);
// 				else
// 					add_child(head, current);
// 				if (!first_file)
// 					first_file = current;
// 			}
// 			prev_file = current;
// 		}
// 		else
// 		{
// 			if (!prev_cmd)
// 			{
// 				if (strcmp(temp->content, "echo\0") == 0
// 				|| strcmp(temp->content, "cd\0") == 0
// 				|| strcmp(temp->content, "pwd\0") == 0
// 				|| strcmp(temp->content, "export\0") == 0
// 				|| strcmp(temp->content, "unset\0") == 0
// 				|| strcmp(temp->content, "env\0") == 0
// 				|| strcmp(temp->content, "exit\0") == 0)
// 					command_node = create_ast_tree_node(NODE_BUILTIN, temp->content);
// 				else
// 					command_node = create_ast_tree_node(NODE_COMMAND, temp->content);
// 				if (!head)
// 					head = command_node;
// 				else
// 					add_child(current, command_node);
// 				prev_cmd = command_node;
// 			}
// 			else
// 				prev_cmd->cmd->cmds = update_cmd(prev_cmd->cmd->cmds, temp->content);
// 		}
// 		temp = temp->next;
// 	}
// 	minishell->ast_node = head;
// }
