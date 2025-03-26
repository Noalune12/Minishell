/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:04 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 12:18:05 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"

int	still_heredoc_left(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp && (is_operator_node(temp->type) == 0
			&& temp->type != NODE_CLOSE_PAR))
	{
		if (temp->type == NODE_HEREDOC)
			return (1);
		temp = temp->next;
	}
	return (0);
}
