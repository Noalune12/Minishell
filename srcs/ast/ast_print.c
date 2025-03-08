#include "minishell.h"

static void print_spaces(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf(" ");
		i++;
	}
}

static void print_node_content(t_ast *node)
{
	if (node->type == NODE_COMMAND)
		print_cmd_node(node, "c");
	else if (node->type == NODE_BUILTIN) // delete ou pas ? on a pas encore identifier si cest un builtin ou pas
		print_cmd_node(node, "b");
	else if (node->type == NODE_PIPE)
		printf("|\n");
	else if (node->type == NODE_REDIR_OUT)
		print_redirect_node(node, ">");
	else if (node->type == NODE_REDIR_IN)
		print_redirect_node(node, "<");
	else if (node->type == NODE_AND)
		printf("&&\n");
	else if (node->type == NODE_OR)
		printf("||\n");
	else if (node->type == NODE_APPEND)
		print_redirect_node(node, ">>");
	else if (node->type == NODE_HEREDOC)
		print_redirect_node(node, "<<");
	else if (node->type == NODE_OPEN_PAR)
		print_redirect_node(node, "(");
	else if (node->type == NODE_CLOSE_PAR)
		print_redirect_node(node, ")");
}

void	print_ast(t_ast *node, int depth, bool *exec_status)
{
	if (exec_status == false || !node)
		return ;
	if (node->right)
		print_ast(node->right, depth + 10, exec_status);
	print_spaces(depth);
	print_node_content(node);
	if (node->left)
		print_ast(node->left, depth + 10, exec_status);
}
