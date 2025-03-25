#include "ast.h"
#include "minishell.h"

void	ft_free(char **split)
{
	size_t	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			split[i] = NULL;
			i++;
		}
		free (split);
		split = NULL;
	}
}

void	free_ast_2(t_minishell *minishell) // TODO make free ast exec without unlink
{
	if (minishell->ast_node == NULL)
		return ;
	if (minishell->ast_node->left != NULL)
		free_ast(minishell->ast_node->left);
	if (minishell->ast_node->right != NULL)
		free_ast(minishell->ast_node->right);
	if (minishell->ast_node->cmd != NULL)
	{
		if (minishell->ast_node->type == NODE_HEREDOC)
			unlink(minishell->ast_node->cmd->cmds[0]);
		free(minishell->ast_node->cmd->path);
		ft_free(minishell->ast_node->cmd->cmds);
		free(minishell->ast_node->cmd);
	}
	if (minishell->ast_node != NULL)
		free(minishell->ast_node);
	minishell->ast_node = NULL; // rigolo
}

void	free_ast(t_ast *node) // TODO make free ast exec without unlink
{
	if (node == NULL)
		return ;
	if (node->left != NULL)
		free_ast(node->left);
	if (node->right != NULL)
		free_ast(node->right);
	if (node->cmd != NULL)
	{
		free(node->cmd->path);
		ft_free(node->cmd->cmds);
		free(node->cmd);
	}
	if (node != NULL)
		free(node);
	node = NULL;
}

t_ast	*error_handling_ast(t_ast *root, t_ast *sub_ast, char *str)
{
	if (root)
		free_ast(root);
	if (sub_ast)
		free_ast(sub_ast);
	ft_dprintf(STDERR_FILENO, "%s", str);
	return (NULL);
}
