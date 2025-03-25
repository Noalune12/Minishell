#include "types.h"
#include "ast.h"
#include "minishell.h"
#include "ft_dprintf.h"

static void	print_spaces(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		write(1, " ", 1);
		i++;
	}
}

static void	print_node_content(t_ast *node)
{
	if (node->type == NODE_COMMAND)
		print_cmd_node(node, "c");
	else if (node->type == NODE_PIPE)
		ft_dprintf(STDERR_FILENO, "|\n");
	else if (node->type == NODE_REDIR_OUT)
		print_redirect_node(node, ">");
	else if (node->type == NODE_REDIR_IN)
		print_redirect_node(node, "<");
	else if (node->type == NODE_AND)
		ft_dprintf(STDERR_FILENO, "&&\n");
	else if (node->type == NODE_OR)
		ft_dprintf(STDERR_FILENO, "||\n");
	else if (node->type == NODE_APPEND)
		print_redirect_node(node, ">>");
	else if (node->type == NODE_HEREDOC)
		print_redirect_node(node, "<<");
	else if (node->type == NODE_OPEN_PAR)
		print_redirect_node(node, "(");
	else if (node->type == NODE_CLOSE_PAR)
		print_redirect_node(node, ")");
}

void	print_ast(t_minishell *ms, t_ast *node, int depth)
{
	if (ms->exec_status == false || ms->options->display_ast == false || !node)
		return ;
	if (node->right)
		print_ast(ms, node->right, depth + 10);
	print_spaces(depth);
	print_node_content(node);
	if (node->left)
		print_ast(ms, node->left, depth + 10);
}
