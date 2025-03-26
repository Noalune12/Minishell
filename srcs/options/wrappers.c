/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:44 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 13:49:07 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "options.h"

void	ast_wrapper(t_minishell *minishell)
{
	print_ast(minishell, minishell->ast_node, 0);
}

void	options_wrapper(t_minishell *minishell)
{
	print_toggled_options(minishell);
}

void	tokens_wrapper(t_minishell *minishell)
{
	print_tokens(minishell);
}
