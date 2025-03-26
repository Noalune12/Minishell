/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_creation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:09 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 09:20:10 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "libft.h"
#include "types.h"

static t_cmd	*add_cmd(char *content)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->path = NULL;
	new_cmd->cmds = malloc(2 * sizeof(char *));
	if (new_cmd->cmds == NULL)
	{
		free(new_cmd);
		return (NULL);
	}
	new_cmd->cmds[0] = ft_strdup(content);
	if (new_cmd->cmds[0] == NULL)
	{
		free(new_cmd->cmds);
		free(new_cmd);
		return (NULL);
	}
	new_cmd->cmds[1] = NULL;
	return (new_cmd);
}

t_ast	*create_ast_tree_node(t_node_type type, char *content,
	bool expand, t_ast *parent)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->cmd = add_cmd(content);
	if (node->cmd == NULL)
	{
		free(node);
		return (NULL);
	}
	if (type == NODE_HEREDOC)
		node->cmd->to_expand = expand;
	else
		node->cmd->to_expand = false;
	node->left = NULL;
	node->right = NULL;
	if (parent && parent->left == NULL)
		parent->left = node;
	else if (parent && parent->right == NULL)
		parent->right = node;
	return (node);
}
