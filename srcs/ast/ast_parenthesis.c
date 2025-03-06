#include "minishell.h"

t_ast *create_parenthesis(t_token *token)
{
	t_token	*temp = token;
	t_ast	*command_node = NULL;
	t_ast	*prev_cmd = NULL;
	t_ast	*current = NULL;
	t_ast	*head = NULL;
	t_ast	*prev_and_or = NULL;
	bool	left = true;
	t_ast *prev_pipe = NULL;
	t_ast *first_file = NULL;
	t_ast *prev_file = NULL;
	t_ast *parenthesis = NULL;
	t_ast *last_pipe = NULL;
	// t_ast *last_or_and = NULL;

	while (temp)
	{
		if (temp->type == NODE_OPEN_PAR)
		{
			// check if is still in parenthesis to recall function
			temp = temp->next;
			parenthesis = create_parenthesis(temp);
			// print_ast(parenthesis, 0);
			while (temp->type == NODE_CLOSE_PAR)
				temp = temp ->next;
			// printf("now temp = %s\n", temp->content);
			// printf("current = %s\n", current->cmd->cmds[0]);
			// printf("\n------current----------\n");
			// print_ast(current, 0);
			// printf("\n------last pipe----------\n");
			// print_ast(last_pipe, 0);
			if (last_pipe && !prev_and_or)
			{
				current->left = last_pipe->right;
				last_pipe->right = current;
				current->right = parenthesis;
				head = last_pipe;
			}
			else if (last_pipe && prev_and_or)
			{
				current->left = last_pipe->right;
				last_pipe->right = current;
				current->right = parenthesis;
			}
			else if (!last_pipe && prev_and_or)
			{
				prev_and_or->right = parenthesis;
				last_pipe = parenthesis;
				prev_pipe = parenthesis;
			}
			else
				head = parenthesis;
			// printf("\n------ast----------\n");
			// print_ast(head, 0);
		}
		else if (temp->type == NODE_AND
			|| temp->type == NODE_OR)
		{
			if (temp->type == NODE_AND)
				current = create_ast_tree_node(NODE_AND, temp->content);
			else
				current = create_ast_tree_node(NODE_OR, temp->content);
			if (head)
				add_child(current, head);
			prev_and_or = current;
			head = current;
			prev_cmd = NULL;
			first_file = NULL;
			prev_pipe = NULL;
			left = false;
			prev_file = NULL;
			last_pipe = NULL;
		}
		else if (temp->type == NODE_PIPE)
		{
			current = create_ast_tree_node(NODE_PIPE, temp->content);
			if (prev_cmd && left == false && !prev_pipe && !first_file)
				current->left = prev_cmd;
			else if (left == false && !prev_pipe && first_file)
				current->left = first_file;
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
			first_file = NULL;
			prev_file = NULL;
			if (temp->type == NODE_OPEN_PAR)
				last_pipe = current;
		}
		else if (temp->type == NODE_REDIR_OUT
		|| temp->type == NODE_REDIR_IN
		|| temp->type == NODE_APPEND
		|| temp->type == NODE_HEREDOC)
		{
			if (temp->type == NODE_REDIR_OUT)
			{
				temp = temp->next;
				current = create_ast_tree_node(NODE_REDIR_OUT, temp->content);
			}
			else if (temp->type == NODE_REDIR_IN)
			{
				temp = temp->next;
				current = create_ast_tree_node(NODE_REDIR_IN, temp->content);
			}
			else if (temp->type == NODE_APPEND)
			{
				temp = temp->next;
				current = create_ast_tree_node(NODE_APPEND, temp->content);
			}
			else
			{
				while (temp->next && (temp->next->type == NODE_COMMAND || temp->next->type == NODE_HEREDOC))
					temp = temp->next;
				current = create_ast_tree_node(NODE_HEREDOC, temp->content);
			}
			if (head && prev_cmd)
			{
				add_child(prev_cmd, current);
				ft_swap(prev_cmd, current);
				if (!first_file)
					first_file = prev_cmd;
				prev_cmd = prev_cmd->left;
			}
			else if (!head)
				head = current;
			else if (prev_pipe && !prev_cmd)
			{
				if (prev_file)
					add_child(prev_file, current);
				else
					add_child(prev_pipe, current);
				if (!first_file)
					first_file = current;
			}
			else if (!prev_cmd)
			{
				if (prev_file)
					add_child(prev_file, current);
				else
					add_child(head, current);
				if (!first_file)
					first_file = current;
			}
			prev_file = current;
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
	return (head);
}
