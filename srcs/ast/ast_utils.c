/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:17 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 09:20:19 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_dprintf.h"
#include "minishell.h"
#include "types.h"
#include "utils.h"

void	free_ast_2(t_minishell *minishell)
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
		ft_free_double(minishell->ast_node->cmd->cmds);
		free(minishell->ast_node->cmd);
	}
	if (minishell->ast_node != NULL)
		free(minishell->ast_node);
	minishell->ast_node = NULL;
}

void	free_ast(t_ast *node)
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
		ft_free_double(node->cmd->cmds);
		free(node->cmd);
	}
	if (node != NULL)
		free(node);
	node = NULL;
}

t_ast	*error_handling_ast(t_ast *root, t_ast *sub_ast)
{
	if (root)
		free_ast(root);
	if (sub_ast)
		free_ast(sub_ast);
	return (NULL);
}
