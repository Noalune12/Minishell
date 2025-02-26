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

t_ast *create_ast_tree_node(t_node_type type, char *content)
{
	t_ast *node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->cmd = add_cmd(content);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void add_child(t_ast *parent, t_ast *child)
{
	if (!parent->left)
		parent->left = child;
	else
		parent->right = child;
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

void create_ast(t_minishell *minishell)
{
	t_list *temp = minishell->token;
	t_ast *command_node = NULL;
	t_ast *prev_cmd = NULL;
	t_ast *current = NULL;
	t_ast *head = NULL;
	t_ast *prev_and_or = NULL;
	bool	left = true;
	t_ast *prev_pipe = NULL;
	t_ast *prev_file = NULL;

	while (temp)
	{
		if (strcmp(temp->content, "&&\0") == 0
			|| strcmp(temp->content, "||\0") == 0)
		{
			if (strcmp(temp->content, "&&\0") == 0)
				current = create_ast_tree_node(NODE_AND, temp->content);
			else
				current = create_ast_tree_node(NODE_OR, temp->content);
			if (head)
				add_child(current, head);
			prev_and_or = current;
			head = current;
			prev_cmd = NULL;
			prev_file = NULL;
			prev_pipe = NULL;
			left = false;
		}
		else if (strcmp(temp->content, "|\0") == 0)
		{
			current = create_ast_tree_node(NODE_PIPE, temp->content);
			if (prev_cmd && left == true)
				current->right = prev_cmd;
			else if (prev_cmd && left == false && !prev_pipe && !prev_file)
				current->left = prev_cmd;
			else if (left == false && !prev_pipe && prev_file)
				current->left = prev_file;
			if (prev_pipe)
			{
				current->left = prev_pipe;
				prev_and_or->right = current;
			}
			if (prev_and_or)
			{
				add_child(prev_and_or, current);
				prev_pipe = current;
			}
			else if (head)
				add_child(current, head);
			if (!prev_and_or)
				head = current;
			prev_cmd = NULL;
			prev_file = NULL;
		}
		else if (strcmp(temp->content, ">\0") == 0
		|| strcmp(temp->content, "<\0") == 0
		|| strcmp(temp->content, ">>\0") == 0
		|| strcmp(temp->content, "<<\0") == 0)
		{
			if (strcmp(temp->content, ">\0") == 0)
			{
				temp = temp->next;
				current = create_ast_tree_node(NODE_REDIR_OUT, temp->content);
			}
			else if (strcmp(temp->content, "<\0") == 0)
			{
				temp = temp->next;
				current = create_ast_tree_node(NODE_REDIR_IN, temp->content);
			}
			else if (strcmp(temp->content, ">>\0") == 0)
			{
				temp = temp->next;
				current = create_ast_tree_node(NODE_APPEND, temp->content);
			}
			else
			{
				temp = temp->next;
				current = create_ast_tree_node(NODE_HEREDOC, temp->content);
			}
			if (head && prev_cmd)
			{
				add_child(prev_cmd, current);
				ft_swap(prev_cmd, current);
				if (!prev_file)
					prev_file = prev_cmd;
				prev_cmd = prev_cmd->left;
			}
			else if (!head)
				head = current;
			else if (prev_pipe && !prev_cmd)
			{
				add_child(prev_pipe, current);
				prev_file = current;
			}
			else if (!prev_cmd)
			{
				add_child(head, current);
				prev_file = current;
			}
		}
		else
		{
			if (!prev_cmd)
			{
				if (strcmp(temp->content, "echo\0") == 0
				|| strcmp(temp->content, "cd\0") == 0
				|| strcmp(temp->content, "pwd\0") == 0
				|| strcmp(temp->content, "export\0") == 0
				|| strcmp(temp->content, "unset\0") == 0
				|| strcmp(temp->content, "env\0") == 0
				|| strcmp(temp->content, "exit\0") == 0)
					command_node = create_ast_tree_node(NODE_BUILTIN, temp->content);
				else
					command_node = create_ast_tree_node(NODE_COMMAND, temp->content);
				if (!head)
					head = command_node;
				else
					add_child(current, command_node);
				prev_cmd = command_node;
			}
			else
				prev_cmd->cmd->cmds = update_cmd(prev_cmd->cmd->cmds, temp->content);
		}
		temp = temp->next;
	}
	minishell->ast_node = head;
}

// ast no bonus
// void create_ast(t_minishell *minishell)
// {
// 	t_list *temp = minishell->token;
// 	t_ast *command_node = NULL;
// 	t_ast *prev_cmd = NULL;
// 	t_ast *current = NULL;
// 	t_ast *head = NULL;

// 	while (temp)
// 	{
// 		if (strcmp(temp->content, "|\0") == 0)
// 		{
// 			current = create_ast_tree_node(NODE_PIPE, temp->content);
// 			if (head)
// 				add_child(current, head);
// 			head = current;
// 			prev_cmd = NULL;
// 		}
// 		else if (strcmp(temp->content, ">\0") == 0
// 		|| strcmp(temp->content, "<\0") == 0
// 		|| strcmp(temp->content, ">>\0") == 0)
// 		{
// 			if (strcmp(temp->content, ">\0") == 0)
// 			{
// 				temp = temp->next;
// 				current = create_ast_tree_node(NODE_REDIR_OUT, temp->content);
// 			}
// 			else if (strcmp(temp->content, "<\0") == 0)
// 			{
// 				temp = temp->next;
// 				current = create_ast_tree_node(NODE_REDIR_IN, temp->content);
// 			}
// 			else
// 			{
// 				temp = temp->next;
// 				current = create_ast_tree_node(NODE_APPEND, temp->content);
// 			}
// 			if (head && prev_cmd)
// 			{
// 				add_child(prev_cmd, current);
// 				ft_swap(prev_cmd, current);
// 				prev_cmd = prev_cmd->left;
// 			}
// 			else if (!head)
// 				head = current;
// 			else if (!prev_cmd)
// 				add_child(head, current);
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
