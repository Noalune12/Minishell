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
	}
}

void	free_ast_2(t_ast *node) // TODO make free ast exec without unlink
{
	if (!node)
		return ;
	if (node->left)
		free_ast(node->left);
	if (node->right)
		free_ast(node->right);
	if (node->cmd)
	{
		if (node->type == NODE_HEREDOC)
			unlink(node->cmd->cmds[0]);
		free(node->cmd->path);
		ft_free(node->cmd->cmds);
		free(node->cmd);
	}
	free(node);
}

void	free_ast(t_ast *node) // TODO make free ast exec without unlink
{
	if (!node)
		return ;
	if (node->left)
		free_ast(node->left);
	if (node->right)
		free_ast(node->right);
	if (node->cmd)
	{
		// if (node->type == NODE_HEREDOC)
		// 	unlink(node->cmd->cmds[0]);
		free(node->cmd->path);
		ft_free(node->cmd->cmds);
		free(node->cmd);
	}
	free(node);
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
