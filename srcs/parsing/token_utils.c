/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:21:28 by gueberso          #+#    #+#             */
/*   Updated: 2025/03/26 09:21:29 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	clear_token_list(t_list *token)
{
	t_list	*current;
	t_list	*next;

	if (!token)
		return ;
	current = token;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
}

t_node_type	get_operator_type(const char *content, \
	size_t i, size_t op_len)
{
	if (ft_strncmp(content + i, "|", op_len) == 0 && op_len == 1)
		return (NODE_PIPE);
	if (ft_strncmp(content + i, "||", op_len) == 0)
		return (NODE_OR);
	if (ft_strncmp(content + i, "&&", op_len) == 0)
		return (NODE_AND);
	if (ft_strncmp(content + i, ">", op_len) == 0 && op_len == 1)
		return (NODE_REDIR_OUT);
	if (ft_strncmp(content + i, "<", op_len) == 0 && op_len == 1)
		return (NODE_REDIR_IN);
	if (ft_strncmp(content + i, ">>", op_len) == 0)
		return (NODE_APPEND);
	if (ft_strncmp(content + i, "<<", op_len) == 0)
		return (NODE_HEREDOC);
	if (ft_strncmp(content + i, "(", op_len) == 0 && op_len == 1)
		return (NODE_OPEN_PAR);
	if (ft_strncmp(content + i, ")", op_len) == 0 && op_len == 1)
		return (NODE_CLOSE_PAR);
	return (NODE_COMMAND);
}

void	handle_quotes(char c, bool *in_quotes, char *quote_type)
{
	if (!*in_quotes)
	{
		*in_quotes = true;
		*quote_type = c;
	}
	else if (c == *quote_type)
	{
		*in_quotes = false;
		*quote_type = 0;
	}
}
