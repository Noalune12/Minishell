#include "minishell.h"

void	find_last_branch(t_minishell *minishell)
{
	t_ast *temp;

	if (!minishell->ast_node)
		return ;
	temp = minishell->ast_node;
	if (temp->type == NODE_PIPE)
		temp = temp->right;
	while (temp)
	{
		temp->last_branch = 1;
		temp = temp->left;
	}
}
