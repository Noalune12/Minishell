/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_identification.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:07 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 12:18:49 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	is_redir_node(t_node_type type)
{
	if (type == NODE_REDIR_OUT
		|| type == NODE_REDIR_IN
		|| type == NODE_APPEND
		|| type == NODE_HEREDOC)
		return (1);
	return (0);
}

int	is_redir_node_not_heredoc(t_node_type type)
{
	if (type == NODE_REDIR_OUT
		|| type == NODE_REDIR_IN
		|| type == NODE_APPEND)
		return (1);
	return (0);
}

int	is_operator_node(t_node_type type)
{
	if (type == NODE_PIPE
		|| type == NODE_OR
		|| type == NODE_AND)
		return (1);
	return (0);
}
