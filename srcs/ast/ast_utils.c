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

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	if (node->left)
		free_ast(node->left);
	if (node->right)
		free_ast(node->right);
	if (node->cmd)
	{
		free(node->cmd->path);
		ft_free(node->cmd->cmds);
		free(node->cmd);
	}
	free(node);
}
