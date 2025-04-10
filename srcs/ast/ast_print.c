/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:20:14 by lbuisson          #+#    #+#             */
/*   Updated: 2025/03/26 13:51:39 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "ast.h"
#include "minishell.h"
#include "options.h"

static void	print_spaces(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		write(1, " ", 1);
		i++;
	}
}

static void	print_node_content(t_ast *node)
{
	if (node->type == NODE_COMMAND)
		print_cmd_node(node, "c");
	else if (node->type == NODE_PIPE)
		printf("|\n");
	else if (node->type == NODE_REDIR_OUT)
		print_redirect_node(node, ">");
	else if (node->type == NODE_REDIR_IN)
		print_redirect_node(node, "<");
	else if (node->type == NODE_AND)
		printf("&&\n");
	else if (node->type == NODE_OR)
		printf("||\n");
	else if (node->type == NODE_APPEND)
		print_redirect_node(node, ">>");
	else if (node->type == NODE_HEREDOC)
		print_redirect_node(node, "<<");
	else if (node->type == NODE_OPEN_PAR)
		print_redirect_node(node, "(");
	else if (node->type == NODE_CLOSE_PAR)
		print_redirect_node(node, ")");
}

void	print_ast(t_minishell *minishell, t_ast *node, int depth)
{
	if (minishell->exec_status == false \
		|| minishell->options->display_ast == false || node == NULL)
		return ;
	if (node->right)
		print_ast(minishell, node->right, depth + 10);
	print_spaces(depth);
	print_node_content(node);
	if (node->left)
		print_ast(minishell, node->left, depth + 10);
}
