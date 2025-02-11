#include "minishell.h"

static void	_print_tree(t_ast *root, size_t space);
static void	format(t_ast *root);

void	print_tree(t_ast *root)
{
	ft_printf("<->-<->-<->-<->-<->-<->-<->-<->-<->-<->-<->-<->-<->-<->\n");
	_print_tree(root, 0);
	ft_printf("\n\n<->-<->-<->-<->-<->-<->-<->-<->-<->-<->-<->-<->-<->-<->\n");
}

static void	_print_tree(t_ast *root, size_t space)
{
	size_t	i;

	i = 6;
	if (root == NULL)
		return ;
	space += 6;
	_print_tree(root->right, space);
	ft_printf("\n");
	while (space > i++)
		ft_printf(" ");
	format(root);
	_print_tree(root->left, space);
}

static void	format(t_ast *root)
{
	size_t	i;

	if (root->type == NODE_COMMAND)
	{
		i = 0;
		while ((root->content) != NULL)
		{
			ft_printf("%s ", root->content);
			i++;
		}
	}
	else if (root->type == NODE_REDIRECTR)
		ft_printf("<:%s", root->content);
	else if (root->type == NODE_REDIRECTL)
		ft_printf(">:%s", root->content);
	else if (root->type == NODE_HERE_DOC)
		ft_printf("<<:%s", root->content);
	else if (root->type == NODE_DREDIRECTL)
		ft_printf(">>:%s", root->content);
	else if (root->type == NODE_AND)
		ft_printf("&&");
	else if (root->type == NODE_OR)
		ft_printf("||");
	else if (root->type == NODE_PIPE)
		ft_printf("|");
}
