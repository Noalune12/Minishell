/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:41 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 13:48:24 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "common.h"
#include "minishell.h"
#include "options.h"

void	print_tokens(t_minishell *minishell)
{
	t_token		*current;
	int			i;
	static char	*type_short[] = {
		"CMD", "PIPE", "OR", "AND", "IN", "OUT",
		"HDOC", "APP", "(", ")", "BUILT"
	};

	if (minishell->options->display_tokens == false)
		return ;
	printf(BOLD_RED"Tokens:\n"RESET);
	current = minishell->token;
	i = 0;
	while (current)
	{
		printf(BOLD_RED"  %d. "RESET, current->type);
		printf("%s%-4s"" → ", CYAN, type_short[current->type]);
		printf("%s%s%s\n", WHITE_BOLD, current->content, RESET);
		current = current->next;
		i++;
	}
	if (minishell->options->display_ast == true)
		printf("\n");
}

int	update_ptokens_wrapper(char **cmds, t_minishell *minishell)
{
	(void) cmds;
	update_options(&minishell->options->display_tokens);
	return (0);
}

int	update_ptree_wrapper(char **cmds, t_minishell *minishell)
{
	(void) cmds;
	update_options(&minishell->options->display_ast);
	return (0);
}
