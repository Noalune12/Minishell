#include "minishell.h"

t_ast *create_parenthesis(t_list *token)
{
	t_list *temp = token;
	t_ast *command_node = NULL;
	t_ast *prev_cmd = NULL;
	t_ast *current = NULL;
	t_ast *head = NULL;
	t_ast *prev_and_or = NULL;
	bool	left = true;
	t_ast *prev_pipe = NULL;
	t_ast *prev_file = NULL;

	while (strcmp(temp->content, ")\0") != 0)
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
				while (temp->next->next && strcmp(temp->next->next->content, "<<\0") == 0)
					temp = temp->next->next;
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
	return (head);
}
