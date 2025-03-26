/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:02 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 13:17:42 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include "exec.h"
#include "minishell.h"
#include "utils.h"

static char	**update_cmd_content(char **cmds, char **new_cmds, char *content)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		new_cmds[i] = ft_strdup(cmds[i]);
		if (new_cmds[i] == NULL)
		{
			ft_free_double(cmds);
			free_tab(new_cmds, i);
			return (NULL);
		}
		i++;
	}
	new_cmds[i] = ft_strdup(content);
	if (new_cmds[i] == NULL)
	{
		ft_free_double(cmds);
		free_tab(new_cmds, i);
		return (NULL);
	}
	new_cmds[i + 1] = NULL;
	return (new_cmds);
}

static char	**update_cmd(char **cmds, char *content)
{
	char	**new_cmds;
	int		i;

	i = 0;
	while (cmds[i])
		i++;
	new_cmds = malloc((i + 2) * sizeof(char *));
	if (new_cmds == NULL)
	{
		ft_free_double(cmds);
		return (NULL);
	}
	if (update_cmd_content(cmds, new_cmds, content) == NULL)
		return (NULL);
	ft_free_double(cmds);
	return (new_cmds);
}

static int	create_redir(t_token **token, t_branch *branch,
	t_ast *root, t_ast *sub_ast)
{
	branch->token_redir = *token;
	(*token) = (*token)->next;
	if (is_redir_node_not_heredoc(branch->token_redir->type)
		|| (branch->token_redir->type == NODE_HEREDOC
			&& still_heredoc_left(*token) == 0))
	{
		branch->node_redir = create_ast_tree_node(branch->token_redir->type,
				(*token)->content, (*token)->to_expand, branch->node_redir);
		if (branch->node_redir == NULL)
		{
			free_ast(branch->node);
			free_ast(branch->node_cmd);
			error_handling_ast(root, sub_ast);
			return (0);
		}
	}
	if (branch->node == NULL)
		branch->node = branch->node_redir;
	return (1);
}

static t_ast	*create_cmd(t_token **token, t_branch *branch,
	t_ast *root, t_ast *sub_ast)
{
	if (branch->node_cmd)
	{
		branch->node_cmd->cmd->cmds = update_cmd(branch->node_cmd->cmd->cmds,
				(*token)->content);
		if (branch->node_cmd->cmd->cmds == NULL)
		{
			free_ast(branch->node);
			free_ast(branch->node_cmd);
			return (error_handling_ast(root, sub_ast));
		}
	}
	else
	{
		branch->node_cmd = create_ast_tree_node(NODE_COMMAND,
				(*token)->content, 0, NULL);
		if (branch->node_cmd == NULL)
		{
			free_ast(branch->node);
			free_ast(branch->node_cmd);
			return (error_handling_ast(root, sub_ast));
		}
	}
	return (branch->node_cmd);
}

t_ast	*create_branch(t_token **token, t_ast *root, t_ast *sub_ast)
{
	t_branch	branch;

	ft_memset(&branch, 0, sizeof(t_branch));
	while ((*token))
	{
		if (is_redir_node((*token)->type))
		{
			if (create_redir(token, &branch, root, sub_ast) == 0)
				return (NULL);
		}
		else if (create_cmd(token, &branch, root, sub_ast) == NULL)
			return (NULL);
		if ((*token)->next && ((is_operator_node((*token)->next->type) \
				|| (*token)->next->type == NODE_CLOSE_PAR)))
			break ;
		(*token) = (*token)->next;
	}
	if (branch.node == NULL)
		branch.node = branch.node_cmd;
	else if (branch.node_redir)
		branch.node_redir->left = branch.node_cmd;
	return (branch.node);
}
